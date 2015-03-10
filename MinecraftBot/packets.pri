SOURCES +=  packet.cpp \
            encryptionrequest.cpp \
            handshake.cpp \
            loginstart.cpp \
            keepalive.cpp \
            encryptionresponse.cpp \
    $$PWD/chatmessage.cpp \
    $$PWD/sendchatmessage.cpp \
    $$PWD/playerpositionandlook.cpp \
    $$PWD/playerposition.cpp \
    $$PWD/clientstatus.cpp \
    $$PWD/onground.cpp

HEADERS += packet.h \
           encryptionrequest.h \
            handshake.h \
            loginstart.h \
            keepalive.h \
            encryptionresponse.h \
    $$PWD/chatmessage.h \
    $$PWD/sendchatmessage.h \
    $$PWD/playerpositionandlook.h \
    $$PWD/playerposition.h \
    $$PWD/clientstatus.h \
    $$PWD/onground.h
