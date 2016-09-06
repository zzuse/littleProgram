#!/bin/ksh
 
while [ true ]
do
#################################
# --- Main Program, DTrace ---
#
/usr/sbin/dtrace -Cs <( print -r '
#pragma D option quiet
#pragma D option dynvarsize=16m
 
uint64_t valid_start_time,start_time[int];
self unsigned char* buf;
self int latency, hbh_id;
self uintptr_t recv_buf;
int total_counter;
 
dtrace:::BEGIN
{
    printf("Tracing...Hit Ctrl-C to end, or terminate in 10 minutes automatically.\n");
    valid_start_time =walltimestamp - 1000000000;
    total_counter = 20;
}
 
syscall::recv:entry
/ arg2 > 64 &&substr(execname, 0, 7) == "odframe" /
{
    self->recv_buf = arg1;
}
 
syscall::recv:return
/ substr(execname, 0, 7) =="odframe" /
{
    self->buf =alloca(20);
   copyinto(self->recv_buf, 20, self->buf);
    self->magic =((unsigned char*)self->buf)[0];
    self->pkg_len =((unsigned int*)self->buf)[0] & 0xFFFFFF;
    self->hbh_id =((unsigned int*)self->buf)[3];
   start_time[self->hbh_id] = (self->magic == 1 && self->pkg_len== arg0) ? walltimestamp : 0;
}
 
syscall::send:entry
{
    self->latency = 0;
}
 
syscall::send:entry
/ arg2 > 64 &&substr(execname, 0, 7) == "odframe" /
{
    self->buf =alloca(20);
    copyinto(arg1, 20,self->buf);
    self->magic =((unsigned char*)self->buf)[0];
    self->pkg_len =((unsigned int*)self->buf)[0] & 0xFFFFFF;
    self->hbh_id =((unsigned int*)self->buf)[3];
    self->latency =(start_time[self->hbh_id] > valid_start_time && self->magic ==1 && self->pkg_len == arg2)
                 ? ((walltimestamp - start_time[self->hbh_id]) /1000000)
                 : 0;
   start_time[self->hbh_id] = 0;
}
 
syscall::send:return
/ self->latency > 0 /
{
    @f1[pid] =avg(self->latency);
    @f2[pid] =max(self->latency);
    @f3[pid] =quantize(self->latency);
    @TotalCalled[pid] =count();
}
 
profile:::tick-30sec
{
    printf("====>%Y\n", walltimestamp);
    printa("\tAverageLatency: pid_%d => %@d ms\n", @f1);
    printa("\tMaxLatency: pid_%d => %@d ms\n", @f2);
    printa("\tCalledTimes: pid_%d => %@d\n", @TotalCalled);
    normalize(@TotalCalled,30);
    printa("\tEvents perSecond: pid_%d => %@d\n", @TotalCalled);
   printa("\tDistribution: pid_%d => %@d\n", @f3);
    trunc(@f1); trunc(@f2);trunc(@f3); trunc(@TotalCalled);
    total_counter--;
}
 
profile:::tick-1sec
/ total_counter <= 0 /
{
    exit(0);
}') 
 
done

