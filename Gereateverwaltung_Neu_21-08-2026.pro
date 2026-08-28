*** Begin Patch
*** Update File: Gereateverwaltung_Neu_21-08-2026.pro
@@
 SOURCES += \
     main.cpp \
     frmmain.cpp \
     statusdelegate.cpp \
     devicedialog.cpp \
     logindialog.cpp \
     authutils.cpp \
     userdialog.cpp
+    ausleihedialog.cpp
 
 HEADERS += \
     frmmain.h \
     statusdelegate.h \
     devicedialog.h \
     logindialog.h \
     authutils.h \
     userdialog.h
+    ausleihedialog.h
@@
 FORMS += \
     frmmain.ui \
     devicedialog.ui \
     logindialog.ui \
     userdialog.ui
+    ausleihedialog.ui
*** End Patch
