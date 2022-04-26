QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    as608.cpp \
    camerathread.cpp \
    change_as608.cpp \
    change_rfid.cpp \
    main.cpp \
    main_interface.cpp \
    manager.cpp \
    motorthread.cpp \
    open_interface.cpp \
    pwd2set.cpp \
    src/bif.cpp \
    src/eigen_faces.cpp \
    src/face_alignment.cpp \
    src/face_basic.cpp \
    src/facemark.cpp \
    src/facemarkAAM.cpp \
    src/facemarkLBF.cpp \
    src/facerec.cpp \
    src/fisher_faces.cpp \
    src/getlandmarks.cpp \
    src/lbph_faces.cpp \
    src/mace.cpp \
    src/predict_collector.cpp \
    src/regtree.cpp \
    src/trainFacemark.cpp \
    uilogin.cpp

HEADERS += \
    as608.h \
    camerathread.h \
    change_as608.h \
    change_rfid.h \
    face/bif.hpp \
    face/face_alignment.hpp \
    face/facemark.hpp \
    face/facemarkAAM.hpp \
    face/facemarkLBF.hpp \
    face/facemark_train.hpp \
    face/facerec.hpp \
    face/mace.hpp \
    face/predict_collector.hpp \
    libjpeg/api_v4l2.h \
    libjpeg/jconfig.h \
    libjpeg/jerror.h \
    libjpeg/jmorecfg.h \
    libjpeg/jpeglib.h \
    main_interface.h \
    manager.h \
    motorthread.h \
    open_interface.h \
    pwd2set.h \
    src/face_alignmentimpl.hpp \
    src/face_utils.hpp \
    src/precomp.hpp \
    uilogin.h

FORMS += \
    change_as608.ui \
    change_rfid.ui \
    main_interface.ui \
    manager.ui \
    open_interface.ui \
    pwd2set.ui \
    uilogin.ui

INCLUDEPATH += /opt/opencv/include
INCLUDEPATH += /opt/opencv/include/opencv
INCLUDEPATH += /opt/opencv/include/opencv2

LIBS += -L/opt/opencv/lib -lopencv_calib3d -lopencv_features2d \
        -lopencv_imgproc -lopencv_shape -lopencv_video \
        -lopencv_core -lopencv_flann -lopencv_ml \
        -lopencv_stitching -lopencv_videostab -lopencv_dnn \
        -lopencv_highgui -lopencv_objdetect -lopencv_superres \
       -lopencv_face -lopencv_imgcodecs -lopencv_photo -lopencv_videoio



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../ui/ui.qrc

DISTFILES += \
    libjpeg/libapi_v4l2_arm.so \
    libjpeg/libjpeg.a \
    libjpeg/libjpeg.so \
    libjpeg/libjpeg.so.8 \
    libjpeg/libjpeg.so.8.0.2 \
    new/MyFaceFisherModel.xml \
    new/MyFaceLBPHModel.xml \
    new/MyFacePCAModel.xml \
    new/haarcascade_frontalface_alt2.xml
