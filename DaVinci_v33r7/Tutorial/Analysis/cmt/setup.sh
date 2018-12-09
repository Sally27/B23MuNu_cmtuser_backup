# echo "Setting Analysis v10r6 in /home/hep/ss4314/cmtuser/DaVinci_v33r7/Tutorial"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/lhcb.cern.ch/lib/contrib/CMT/v1r20p20090520; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=Analysis -version=v10r6 -path=/home/hep/ss4314/cmtuser/DaVinci_v33r7/Tutorial  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

