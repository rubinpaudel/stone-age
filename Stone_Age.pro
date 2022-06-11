QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CivilizationCards/additionalcivilizationcard.cpp \
    CivilizationCards/agriculturecivilizationcard.cpp \
    CivilizationCards/itemdicecivilizationcard.cpp \
    CivilizationCards/pointscivilizationcard.cpp \
    CivilizationCards/resourcechoicecivilizationcard.cpp \
    CivilizationCards/resourcecivilizationcard.cpp \
    CivilizationCards/resourcedicecivilizationcard.cpp \
    CivilizationCards/toolcivilizationcard.cpp \
    CivilizationCards/uniquetoolcivilizationcard.cpp \
    activecivilizationcard.cpp \
    board.cpp \
    buildingcard.cpp \
    buildingcardsdeck.cpp \
    filehandler.cpp \
    tooldeck.cpp \
    views/activecardview.cpp \
    views/buildingcardmodal.cpp \
    civilizationcard.cpp \
    civilizationcardsdeck.cpp \
    views/buildingcardsdeckview.cpp \
    dice.cpp \
    fieldlocation.cpp \
    fixedbuildingcard.cpp \
    game.cpp \
    hutlocation.cpp \
    location.cpp \
    locationplace.cpp \
    main.cpp \
    player.cpp \
    resource.cpp \
    tool.cpp \
    resourcelocation.cpp \
    toolmakerlocation.cpp \
    variablebuildingcard.cpp \
    views/buildingcardsviewer.cpp \
    views/civilizationcardmodal.cpp \
    views/civilizationcardsviewer.cpp \
    views/foodmodal.cpp \
    views/gamescene.cpp \
    views/gamewidget.cpp \
    views/gamewindow.cpp \
    roundhandler.cpp \
    views/itemdicemodal.cpp \
    views/playeritem.cpp \
    views/playerwidget.cpp \
    views/resourcechoicemodal.cpp \
    views/resourcelocationmodal.cpp \
    views/resourcepicker.cpp \
    views/resourcepickerwidget.cpp \
    views/roundstatusbar.cpp \
    views/locationrectitem.cpp \
    views/startscreen.cpp \
    views/toolbutton.cpp \
    views/toolrectitem.cpp \
    views/winnermodal.cpp

HEADERS += \
    CivilizationCards/additionalcivilizationcard.h \
    CivilizationCards/agriculturecivilizationcard.h \
    CivilizationCards/itemdicecivilizationcard.h \
    CivilizationCards/pointscivilizationcard.h \
    CivilizationCards/resourcechoicecivilizationcard.h \
    CivilizationCards/resourcecivilizationcard.h \
    CivilizationCards/resourcedicecivilizationcard.h \
    CivilizationCards/toolcivilizationcard.h \
    CivilizationCards/uniquetoolcivilizationcard.h \
    activecivilizationcard.h \
    board.h \
    buildingcard.h \
    buildingcardsdeck.h \
    filehandler.h \
    tooldeck.h \
    views/activecardview.h \
    views/buildingcardmodal.h \
    civilizationcard.h \
    civilizationcardsdeck.h \
    views/buildingcardsdeckview.h \
    dice.h \
    fieldlocation.h \
    fixedbuildingcard.h \
    game.h \
    hutlocation.h \
    location.h \
    locationplace.h \
    player.h \
    resource.h \
    tool.h \
    resourcelocation.h \
    toolmakerlocation.h \
    variablebuildingcard.h \
    views/buildingcardsviewer.h \
    views/civilizationcardmodal.h \
    views/civilizationcardsviewer.h \
    views/foodmodal.h \
    views/gamescene.h \
    views/gamewidget.h \
    views/gamewindow.h \
    roundhandler.h \
    views/itemdicemodal.h \
    views/playeritem.h \
    views/playerwidget.h \
    views/locationrectitem.h \
    views/resourcechoicemodal.h \
    views/resourcelocationmodal.h \
    views/resourcepicker.h \
    views/resourcepickerwidget.h \
    views/roundstatusbar.h \
    views/startscreen.h \
    views/toolbutton.h \
    views/toolrectitem.h \
    views/winnermodal.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/load.png \
    resources/quit.png \
    resources/save.png \
    resources/new.png \
    saves/config.json \
    saves/playerBuildingCardConfig.json \
    saves/playerTools.json \
    style.qss

RESOURCES += \
    resources.qrc
