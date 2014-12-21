#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T16:45:46
#
#-------------------------------------------------

QT       += core gui

TARGET = reversi-learning
CONFIG   += console
CONFIG   -= app_bundle

# OpenMP
QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

TEMPLATE = app


SOURCES += main.cpp \
    reversi/core/gamemaster.cpp \
    reversi/core/gameboard.cpp \
    reversi/player/tutorialplayer.cpp \
    reversi/player/treeaiplayer.cpp \
    reversi/player/staticruleaiplayer.cpp \
    reversi/player/randomaiplayer.cpp \
    reversi/player/player.cpp \
    reversi/player/neuralnetworkaiplayer.cpp \
    reversi/player/humanplayer.cpp \
    reversi/player/greedyaiplayer.cpp \
    reversi/player/controlaiplayer.cpp \
    reversi/player/balancedaiplayer.cpp \
    reversi/player/assemblyaiplayer.cpp \
    reversi/player/adaptivetreeaiplayer.cpp \
    reversi/player/AssemblyAIPlayer/movementcore.cpp \
    reversi/player/AssemblyAIPlayer/insanecore.cpp \
    reversi/player/AssemblyAIPlayer/greedycore.cpp \
    reversi/player/AssemblyAIPlayer/frontierdiscscore.cpp \
    reversi/player/AssemblyAIPlayer/freemovecore.cpp \
    reversi/player/AssemblyAIPlayer/edgecore.cpp \
    reversi/player/AssemblyAIPlayer/cornercore.cpp \
    reversi/player/AssemblyAIPlayer/core.cpp \
    reversi/player/AssemblyAIPlayer/centercore.cpp \
    reversi/player/AssemblyAIPlayer/assemblyaihelper.cpp \
    reversi/player/AssemblyAIPlayer/areacontrolcore.cpp \
    reversi/player/rules/rulehelper.cpp \
    reversi/player/rules/rule.cpp \
    reversi/player/rules/openingrule.cpp \
    reversi/player/rules/minimiseopponentmovementrule.cpp \
    reversi/player/rules/maximiseownmovementrule.cpp \
    reversi/player/rules/greedyrule.cpp \
    reversi/player/rules/fewerfrontierdiscsrule.cpp \
    reversi/player/rules/endgamerule.cpp \
    reversi/player/rules/cornerrule.cpp \
    getscore.cpp \
    gene.cpp

HEADERS += \
    reversi/core/gamemaster.h \
    reversi/core/gameboard.h \
    reversi/player/tutorialplayer.h \
    reversi/player/treeaiplayer.h \
    reversi/player/staticruleaiplayer.h \
    reversi/player/randomaiplayer.h \
    reversi/player/player.h \
    reversi/player/neuralnetworkaiplayer.h \
    reversi/player/humanplayer.h \
    reversi/player/greedyaiplayer.h \
    reversi/player/controlaiplayer.h \
    reversi/player/balancedaiplayer.h \
    reversi/player/assemblyaiplayer.h \
    reversi/player/adaptivetreeaiplayer.h \
    reversi/player/AssemblyAIPlayer/movementcore.h \
    reversi/player/AssemblyAIPlayer/insanecore.h \
    reversi/player/AssemblyAIPlayer/greedycore.h \
    reversi/player/AssemblyAIPlayer/frontierdiscscore.h \
    reversi/player/AssemblyAIPlayer/freemovecore.h \
    reversi/player/AssemblyAIPlayer/edgecore.h \
    reversi/player/AssemblyAIPlayer/cornercore.h \
    reversi/player/AssemblyAIPlayer/core.h \
    reversi/player/AssemblyAIPlayer/centercore.h \
    reversi/player/AssemblyAIPlayer/assemblyaihelper.h \
    reversi/player/AssemblyAIPlayer/areacontrolcore.h \
    reversi/player/rules/rulehelper.h \
    reversi/player/rules/rule.h \
    reversi/player/rules/openingrule.h \
    reversi/player/rules/minimiseopponentmovementrule.h \
    reversi/player/rules/maximiseownmovementrule.h \
    reversi/player/rules/greedyrule.h \
    reversi/player/rules/fewerfrontierdiscsrule.h \
    reversi/player/rules/endgamerule.h \
    reversi/player/rules/cornerrule.h \
    getscore.h \
    gene.h

OTHER_FILES += \
    reversi/player/NeuralNetworkAIPlayer/inputToHidden.txt \
    reversi/player/NeuralNetworkAIPlayer/hiddenToOutput.txt \
    LICENSE.txt \
    README.md

RESOURCES += \
    reversi/player/NeuralNetworkAIPlayer/NNData.qrc
