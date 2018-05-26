# mp4-recovery-untrack-with-no-moov
recovery mp4 file with no moov tag, support h264 video codec


this is an Android test code dedicated for truncated MP4 file recovery.


Truncated MP4 file is a video file, which have valid structure but it is missing with moov atom. The moov atom is containing basic information necessary to properly interpret and play a video file.

To recover truncated MP4 it is necessary to restore required moov header. To restore the header, another valid MP4 file recorded with the same settings is needed to copy basic configuration. Another part of information is obtained directly from the stream of the truncated file.

As a base for this library the https://github.com/ponchio/untrunc/ was used. It has been improved in order to increase performance and to remove all libav dependency. However, the original code for supporting different video file formats has been removed and limited to H.264/MPEG-4 AVC formats supported by Android MediaRecorder.


Prepare libav
Execute following instructions in root directory of the repository:

wget http://libav.org/releases/libav-12.3.tar.xz
tar xf libav-12.3.tar.xz
(cd libav-12.2; ./configure)
(cd libav-12.2; make)



this code is compiled sucess in qcom 8953 64bits platform and test ok!
