# !!!!
# VEZI ca AICI iti TREBUIE obligatoriu<
# sa ai $$PWD specificat pentru toate PATH-urile
# $$PWD/PrintTest.cpp
# $$PWD/PrintTest.h
# INCLUDEPATH += $$PWD
# / \
#  |
# din CAUZA ca FISIERUL.asta este INCLUS.in toate
# celelalte FISIERE

# add common source files
SOURCES += \
    $$PWD/PrjMenu.cpp \
    $$PWD/BuildMenu.cpp

# add common header files (not strictly necessary for compilation)
HEADERS +=  \
    $$PWD/PrjMenu.h \
    $$PWD/BuildMenu.h

# include/depend path for the common headers
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
