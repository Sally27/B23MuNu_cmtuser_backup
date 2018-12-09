# echo "Setting StrippingArchive v1r25p1 in /home/hep/ss4314/cmtuser/DaVinci_v36r1p3/Phys"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/lhcb.cern.ch/lib/contrib/CMT/v1r20p20090520; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh

tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=StrippingArchive -version=v1r25p1 -path=/home/hep/ss4314/cmtuser/DaVinci_v36r1p3/Phys  -no_cleanup $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

