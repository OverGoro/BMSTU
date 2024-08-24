QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/adapter
INCLUDEPATH += $$PWD/adapter/camera_adapter
INCLUDEPATH += $$PWD/adapter/carcas_data_adapter
INCLUDEPATH += $$PWD/adapter/carcas_model_adapter
INCLUDEPATH += $$PWD/adapter/composite_adapter
INCLUDEPATH += $$PWD/adapter/Factory
INCLUDEPATH += $$PWD/adapter/point_adapter
INCLUDEPATH += $$PWD/auxillary_classes
INCLUDEPATH += $$PWD/command
INCLUDEPATH += $$PWD/containers
INCLUDEPATH += $$PWD/drawer
INCLUDEPATH += $$PWD/exceptions
INCLUDEPATH += $$PWD/facade
INCLUDEPATH += $$PWD/load/builders
INCLUDEPATH += $$PWD/load/builders/camera
INCLUDEPATH += $$PWD/load/builders/model
INCLUDEPATH += $$PWD/load/builders/scene
INCLUDEPATH += $$PWD/load/directors
INCLUDEPATH += $$PWD/load/directors/camera
INCLUDEPATH += $$PWD/load/directors/model
INCLUDEPATH += $$PWD/load/directors/readers
INCLUDEPATH += $$PWD/load/directors/scene
INCLUDEPATH += $$PWD/load/moderators
INCLUDEPATH += $$PWD/load/moderators/camera
INCLUDEPATH += $$PWD/load/moderators/creators
INCLUDEPATH += $$PWD/load/moderators/model
INCLUDEPATH += $$PWD/load/moderators/scene
INCLUDEPATH += $$PWD/manager
INCLUDEPATH += $$PWD/manager/creators
INCLUDEPATH += $$PWD/object
INCLUDEPATH += $$PWD/object/invisible_object
INCLUDEPATH += $$PWD/object/invisible_object/camera
INCLUDEPATH += $$PWD/object/visible_object
INCLUDEPATH += $$PWD/object/visible_object/model
INCLUDEPATH += $$PWD/object/visible_object/model/carcas_model
INCLUDEPATH += $$PWD/scene

SOURCES +=  $$PWD/adapter/camera_adapter/MovePerspectiveCameraAdapter.cpp \
            $$PWD/adapter/camera_adapter/RotatePerspectiveCameraAdapter.cpp \
            $$PWD/adapter/camera_adapter/ScalePerspectiveCameraAdapter.cpp \
            $$PWD/adapter/carcas_data_adapter/MoveCarcasDataAdapter.cpp \
            $$PWD/adapter/carcas_data_adapter/RotateCarcasDataAdapter.cpp \
            $$PWD/adapter/carcas_data_adapter/ScaleCarcasDataAdapter.cpp \
            $$PWD/adapter/carcas_model_adapter/BaseModelAdapter.cpp \
            $$PWD/adapter/carcas_model_adapter/DrawCarcasModelAdapter.cpp \
            $$PWD/adapter/carcas_model_adapter/MoveCarcasModelAdapter.cpp \
            $$PWD/adapter/carcas_model_adapter/RotateCarcasModelAdapter.cpp \
            $$PWD/adapter/carcas_model_adapter/ScaleCarcasModelAdapter.cpp \
            $$PWD/adapter/composite_adapter/DrawCompositeAdapter.cpp \
            $$PWD/adapter/composite_adapter/MoveCompositeAdapter.cpp \
            $$PWD/adapter/composite_adapter/RotateCompositeAdapter.cpp \
            $$PWD/adapter/composite_adapter/ScaleCompositeAdapter.cpp \
            $$PWD/adapter/Factory/DrawAdapterSolution.cpp \
            $$PWD/adapter/Factory/MoveAdapterSolution.cpp \
            $$PWD/adapter/Factory/RotateAdapterSolution.cpp \
            $$PWD/adapter/Factory/ScaleAdapterSolution.cpp \
            $$PWD/adapter/Factory/TransformAdapterSolution.cpp \
            $$PWD/adapter/point_adapter/MovePointAdapter.cpp \
            $$PWD/adapter/point_adapter/RotatePointAdapter.cpp \
            $$PWD/adapter/point_adapter/ScalePointAdapter.cpp \
            $$PWD/command/basecommand.cpp \
            $$PWD/command/cameracommand.cpp \
            $$PWD/command/modelcommand.cpp \
            $$PWD/command/modelscommand.cpp \
            $$PWD/command/scenecommand.cpp \
            $$PWD/drawer/QTDrawer.cpp \
            $$PWD/drawer/QtFactory.cpp \
            $$PWD/exceptions/Exceptions.cpp \
            $$PWD/facade/Facade.cpp \
            # $$PWD/load/builders/camera/BaseCameraBuilder.cpp \
            $$PWD/load/builders/camera/BasePerspectiveCameraBuilder.cpp \
            $$PWD/load/builders/camera/PerspectiveCameraBuilder.cpp \
            $$PWD/load/builders/model/BaseCarcasModelBuilder.cpp \
            $$PWD/load/builders/model/CarcasModelBuilder.cpp \
            $$PWD/load/builders/scene/BaseSceneBuilder.cpp \
            $$PWD/load/builders/scene/SceneBuilder.cpp \
            $$PWD/load/directors/camera/FilePerspectiveCameraBuildDirector.cpp \
            $$PWD/load/directors/model/FileCarcasModelBuildDirector.cpp \
            $$PWD/load/directors/readers/CarcasModelReaderFactory.cpp \
            $$PWD/load/directors/readers/FileCarcasModelReader.cpp \
            $$PWD/load/directors/readers/FilePerspectiveCameraReader.cpp \
            $$PWD/load/directors/scene/FileSceneBuildDirector.cpp \
            $$PWD/load/moderators/camera/CameraLoadModerator.cpp \
            $$PWD/load/moderators/creators/CameraLoadModeratorCreator.cpp \
            $$PWD/load/moderators/creators/ModelLoadModeratorCreator.cpp \
            $$PWD/load/moderators/creators/SceneLoadModeratorCraetor.cpp \
            $$PWD/load/moderators/model/ModelLoadModerator.cpp \
            $$PWD/load/moderators/scene/SceneLoadModerator.cpp \
            $$PWD/main.cpp \
            $$PWD/mainwindow.cpp \
            $$PWD/manager/creators/DrawManagerCreator.cpp \
            $$PWD/manager/creators/LoadManagerCreator.cpp \
            $$PWD/manager/creators/SceneManagerCreator.cpp \
            $$PWD/manager/creators/TransformManagerCreator.cpp \
            $$PWD/manager/DrawManager.cpp \
            $$PWD/manager/TransformManager.cpp \
            $$PWD/object/BaseObject.cpp \
            $$PWD/object/CompositeObject.cpp \
            $$PWD/object/invisible_object/camera/PerspectiveCamera.cpp \
            $$PWD/object/invisible_object/InvisibleObject.cpp \
            $$PWD/object/visible_object/model/BaseModel.cpp \
            $$PWD/object/visible_object/model/carcas_model/CarcasData.cpp \
            $$PWD/object/visible_object/model/carcas_model/CarcasModel.cpp \
            $$PWD/object/visible_object/model/carcas_model/Edge.cpp \
            $$PWD/object/visible_object/model/carcas_model/Point.cpp \
            $$PWD/object/visible_object/VisibleObject.cpp \
            $$PWD/scene/Scene.cpp \
            adapter/Factory/ProjectionAdapterSolution.cpp \
            adapter/Factory/centeradaptersolution.cpp \
            adapter/camera_adapter/centerperspectivecameraadapter.cpp \
            adapter/camera_adapter/projectionperspectivecameraadapter.cpp \
            adapter/carcas_data_adapter/centercarcasdataadapter.cpp \
            adapter/carcas_data_adapter/drawcarcasdataadapter.cpp \
            adapter/carcas_model_adapter/centercarcasmodeladapter.cpp \
            adapter/composite_adapter/centercompositeadapter.cpp \
            adapter/polygon_adapter/MovePolygonAdapter.cpp \
            adapter/polygon_adapter/RotatePolygonAdapter.cpp \
            adapter/polygon_adapter/ScalePolygonAdapter.cpp \
            adapter/polygon_adapter/drawpolygonadapter.cpp \
            adapter/polygon_data_adapter/MovePolygonDataAdapter.cpp \
            adapter/polygon_data_adapter/RotatePolygonDataAdapter.cpp \
            adapter/polygon_data_adapter/ScalePolygonDataAdapter.cpp \
            adapter/polygon_data_adapter/centerpolygondataadapter.cpp \
            adapter/polygon_data_adapter/drawpolygondataadapter.cpp \
            adapter/polygon_model_adapter/DrawPolygonModelAdapter.cpp \
            adapter/polygon_model_adapter/MovePolygonModelAdapter.cpp \
            adapter/polygon_model_adapter/RotatePolygonModelAdapter.cpp \
            adapter/polygon_model_adapter/ScalePolygonModelAdapter.cpp \
            adapter/polygon_model_adapter/basepolygonmodeladapter.cpp \
            adapter/polygon_model_adapter/centerpolygonmodeladapter.cpp \
            auxillary_classes/polygon.cpp \
            load/builders/model/polygonmodelbuilder.cpp \
            load/directors/model/polygonmodelbuilddirector.cpp \
            load/directors/readers/filepolygonmodelreader.cpp \
            load/directors/readers/objcarcasmodelreader.cpp \
            load/directors/readers/objpolygonmodelreader.cpp \
            load/directors/readers/perspectivecamerareaderfactory.cpp \
            load/directors/readers/polygonmodelreaderfactory.cpp \
            load/moderators/creators/polygonmodelloadmoderatorcreator.cpp \
            load/moderators/model/polygonmodelloadmoderator.cpp \
            manager/LoadManager.cpp \
            object/visible_object/model/polygon_model/polygondata.cpp \
            object/visible_object/model/polygon_model/polygonmodel.cpp
HEADERS += $$PWD/auxillary_classes/TransformParams.hpp \
    adapter/Factory/ProjectionAdapterSolution.h \
    adapter/Factory/centeradaptersolution.h \
    adapter/camera_adapter/basePerspectivecameraadapter.h \
    adapter/camera_adapter/centerPerspectivecameraadapter.h \
    adapter/camera_adapter/projectionPerspectivecameraadapter.h \
    adapter/carcas_data_adapter/centercarcasdataadapter.h \
    adapter/carcas_data_adapter/drawcarcasdataadapter.h \
    adapter/carcas_model_adapter/centercarcasmodeladapter.h \
    adapter/composite_adapter/centercompositeadapter.h \
    adapter/polygon_adapter/MovePolygonAdapter.h \
    adapter/polygon_adapter/RotatePolygonAdapter.h \
    adapter/polygon_adapter/ScalePolygonAdapter.h \
    adapter/polygon_adapter/basepolygonadapter.h \
    adapter/polygon_adapter/drawpolygonadapter.h \
    adapter/polygon_data_adapter/BasePolygonDataAdapter.h \
    adapter/polygon_data_adapter/MovePolygonDataAdapter.h \
    adapter/polygon_data_adapter/RotatePolygonDataAdapter.h \
    adapter/polygon_data_adapter/ScalePolygonDataAdapter.h \
    adapter/polygon_data_adapter/centerpolygondataadapter.h \
    adapter/polygon_data_adapter/drawpolygondataadapter.h \
    adapter/polygon_model_adapter/DrawPolygonModelAdapter.h \
    adapter/polygon_model_adapter/MovePolygonModelAdapter.h \
    adapter/polygon_model_adapter/RotatePolygonModelAdapter.h \
    adapter/polygon_model_adapter/ScalePolygonModelAdapter.h \
    adapter/polygon_model_adapter/basepolygonmodeladapter.h \
    adapter/polygon_model_adapter/centerpolygonmodeladapter.h \
    auxillary_classes/polygon.h \
    load/builders/model/polygonmodelbuilder.h \
    load/directors/model/polygonmodelbuilddirector.h \
    load/directors/readers/basepolygonmodelreader.h \
    load/directors/readers/filepolygonmodelreader.h \
    load/directors/readers/objcarcasmodelreader.h \
    load/directors/readers/Perspectivecamerareaderfactory.h \
    load/directors/readers/objpolygonmodelreader.h \
    load/directors/readers/polygonmodelreaderfactory.h \
    load/moderators/creators/polygonmodelloadmoderatorcreator.h \
    load/moderators/model/polygonmodelloadmoderator.h \
    object/visible_object/model/polygon_model/polygondata.h \
    object/visible_object/model/polygon_model/polygonmodel.h
HEADERS += $$PWD/containers/VectorContainer.hpp
HEADERS += $$PWD/drawer/DrawerSolution.hpp
HEADERS += $$PWD/manager/TransformManager.hpp
HEADERS += $$PWD/adapter/BaseAdapter.h
HEADERS += $$PWD/adapter/BasePointAdapter.h
HEADERS += $$PWD/adapter/camera_adapter/BaseCameraAdapter.h
HEADERS += $$PWD/adapter/camera_adapter/MovePerspectiveCameraAdapter.h
HEADERS += $$PWD/adapter/camera_adapter/RotatePerspectiveCameraAdapter.h
HEADERS += $$PWD/adapter/camera_adapter/ScalePerspectiveCameraAdapter.h
HEADERS += $$PWD/adapter/carcas_data_adapter/BaseCarcasDataAdapter.h
HEADERS += $$PWD/adapter/carcas_data_adapter/MoveCarcasDataAdapter.h
HEADERS += $$PWD/adapter/carcas_data_adapter/RotateCarcasDataAdapter.h
HEADERS += $$PWD/adapter/carcas_data_adapter/ScaleCarcasDataAdapter.h
HEADERS += $$PWD/adapter/carcas_model_adapter/BaseModelAdapter.h
HEADERS += $$PWD/adapter/carcas_model_adapter/DrawCarcasModelAdapter.h
HEADERS += $$PWD/adapter/carcas_model_adapter/MoveCarcasModelAdapter.h
HEADERS += $$PWD/adapter/carcas_model_adapter/RotateCarcasModelAdapter.h
HEADERS += $$PWD/adapter/carcas_model_adapter/ScaleCarcasModelAdapter.h
HEADERS += $$PWD/adapter/composite_adapter/BaseCompositeAdapter.h
HEADERS += $$PWD/adapter/composite_adapter/DrawCompositeAdapter.h
HEADERS += $$PWD/adapter/composite_adapter/MoveCompositeAdapter.h
HEADERS += $$PWD/adapter/composite_adapter/RotateCompositeAdapter.h
HEADERS += $$PWD/adapter/composite_adapter/ScaleCompositeAdapter.h
HEADERS += $$PWD/adapter/Factory/DrawAdapterSolution.h
HEADERS += $$PWD/adapter/Factory/MoveAdapterSolution.h
HEADERS += $$PWD/adapter/Factory/RotateAdapterSolution.h
HEADERS += $$PWD/adapter/Factory/ScaleAdapterSolution.h
HEADERS += $$PWD/adapter/Factory/TransformAdapterSolution.h
HEADERS += $$PWD/adapter/point_adapter/MovePointAdapter.h
HEADERS += $$PWD/adapter/point_adapter/RotatePointAdapter.h
HEADERS += $$PWD/adapter/point_adapter/ScalePointAdapter.h
HEADERS += $$PWD/command/basecommand.h
HEADERS += $$PWD/command/cameracommand.h
HEADERS += $$PWD/command/modelcommand.h
HEADERS += $$PWD/command/modelscommand.h
HEADERS += $$PWD/command/scenecommand.h
HEADERS += $$PWD/containers/BaseContainer.h
HEADERS += $$PWD/containers/VectorContainer.h
HEADERS += $$PWD/drawer/AbstractDrawerFactory.h
HEADERS += $$PWD/drawer/BaseDrawer.h
HEADERS += $$PWD/drawer/DrawerSolution.h
HEADERS += $$PWD/drawer/QTDrawer.h
HEADERS += $$PWD/drawer/QtFactory.h
HEADERS += $$PWD/exceptions/Exceptions.h
HEADERS += $$PWD/facade/Facade.h
HEADERS += $$PWD/load/builders/BaseBuilder.h
# HEADERS += $$PWD/load/builders/camera/BaseCameraBuilder.h
HEADERS += $$PWD/load/builders/camera/BasePerspectiveCameraBuilder.h
HEADERS += $$PWD/load/builders/camera/PerspectiveCameraBuilder.h
HEADERS += $$PWD/load/builders/model/BaseCarcasModelBuilder.h
HEADERS += $$PWD/load/builders/model/CarcasModelBuilder.h
HEADERS += $$PWD/load/builders/scene/BaseSceneBuilder.h
HEADERS += $$PWD/load/builders/scene/SceneBuilder.h
HEADERS += $$PWD/load/directors/BaseDirector.h
HEADERS += $$PWD/load/directors/camera/BasePerspectiveCameraBuildDirector.h
HEADERS += $$PWD/load/directors/camera/FilePerspectiveCameraBuildDirector.h
HEADERS += $$PWD/load/directors/model/BaseCarcasModelBuildDirector.h
HEADERS += $$PWD/load/directors/model/FileCarcasModelBuildDirector.h
HEADERS += $$PWD/load/directors/readers/BaseCarcasModelReader.h
HEADERS += $$PWD/load/directors/readers/BasePerspectiveCameraReader.h
HEADERS += $$PWD/load/directors/readers/CarcasModelReaderFactory.h
HEADERS += $$PWD/load/directors/readers/FileCarcasModelReader.h
HEADERS += $$PWD/load/directors/readers/FilePerspectiveCameraReader.h
HEADERS += $$PWD/load/directors/scene/BaseSceneBuildDirector.h
HEADERS += $$PWD/load/directors/scene/FileSceneBuildDirector.h
HEADERS += $$PWD/load/moderators/BaseLoadModerator.h
HEADERS += $$PWD/load/moderators/camera/CameraLoadModerator.h
HEADERS += $$PWD/load/moderators/creators/CameraLoadModeratorCreator.h
HEADERS += $$PWD/load/moderators/creators/ModelLoadModeratorCreator.h
HEADERS += $$PWD/load/moderators/creators/ModeratorSolution.h
HEADERS += $$PWD/load/moderators/creators/SceneLoadModeratorCraetor.h
HEADERS += $$PWD/load/moderators/model/ModelLoadModerator.h
HEADERS += $$PWD/load/moderators/scene/SceneLoadModerator.h
HEADERS += $$PWD/mainwindow.h
HEADERS += $$PWD/manager/BaseManager.h
HEADERS += $$PWD/manager/creators/DrawManagerCreator.h
HEADERS += $$PWD/manager/creators/LoadManagerCreator.h
HEADERS += $$PWD/manager/creators/ManagerSolution.h
HEADERS += $$PWD/manager/creators/SceneManagerCreator.h
HEADERS += $$PWD/manager/creators/TransformManagerCreator.h
HEADERS += $$PWD/manager/DrawManager.h
HEADERS += $$PWD/manager/LoadManager.h
HEADERS += $$PWD/manager/SceneManager.h
HEADERS += $$PWD/object/BaseObject.h
HEADERS += $$PWD/object/CompositeObject.h
HEADERS += $$PWD/object/invisible_object/camera/BaseCamera.h
HEADERS += $$PWD/object/invisible_object/camera/PerspectiveCamera.h
HEADERS += $$PWD/object/invisible_object/InvisibleObject.h
HEADERS += $$PWD/object/visible_object/model/BaseModel.h
HEADERS += $$PWD/object/visible_object/model/carcas_model/CarcasData.h
HEADERS += $$PWD/object/visible_object/model/carcas_model/CarcasModel.h
HEADERS += $$PWD/object/visible_object/model/carcas_model/Edge.h
HEADERS += $$PWD/object/visible_object/model/carcas_model/Point.h
HEADERS += $$PWD/object/visible_object/VisibleObject.h
HEADERS += $$PWD/scene/Scene.h


FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
