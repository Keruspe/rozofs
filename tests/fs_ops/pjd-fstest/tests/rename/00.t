#!/bin/sh
# $FreeBSD: src/tools/regression/fstest/tests/rename/00.t,v 1.1 2007/01/17 01:42:10 pjd Exp $

desc="rename changes file name"

dir=`dirname $0`
. ${dir}/../misc.sh

echo "1..24"

n0=`namegen`
n1=`namegen`
n2=`namegen`
n3=`namegen`

expect 0 mkdir ${n3} 0755
cdir=`pwd`
cd ${n3}

expect 0 mkdir ${n0} 0755
expect dir,0755 lstat ${n0} type,mode
inode=`${fstest} lstat ${n0} inode`
expect 0 rename ${n0} ${n1}
expect ENOENT lstat ${n0} type,mode
expect dir,${inode},0755 lstat ${n1} type,inode,mode
expect 0 rmdir ${n1}

# successful rename(2) updates ctime.
expect 0 create ${n0} 0644
ctime1=`${fstest} stat ${n0} ctime`
sleep 1
expect 0 rename ${n0} ${n1}
ctime2=`${fstest} stat ${n1} ctime`
test_check $ctime1 -lt $ctime2
expect 0 unlink ${n1}

expect 0 mkdir ${n0} 0755
ctime1=`${fstest} stat ${n0} ctime`
sleep 1
expect 0 rename ${n0} ${n1}
ctime2=`${fstest} stat ${n1} ctime`
test_check $ctime1 -lt $ctime2
expect 0 rmdir ${n1}

# unsuccessful link(2) does not update ctime.
expect 0 create ${n0} 0644
ctime1=`${fstest} stat ${n0} ctime`
sleep 1
expect EACCES -u 65534 rename ${n0} ${n1}
ctime2=`${fstest} stat ${n0} ctime`
test_check $ctime1 -eq $ctime2
expect 0 unlink ${n0}

expect 0 mkdir ${n0} 0755
ctime1=`${fstest} stat ${n0} ctime`
sleep 1
expect EACCES -u 65534 rename ${n0} ${n1}
ctime2=`${fstest} stat ${n0} ctime`
test_check $ctime1 -eq $ctime2
expect 0 rmdir ${n0}

cd ${cdir}
expect 0 rmdir ${n3}
