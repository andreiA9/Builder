TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = Components \
          CompileTool \
          BuildManager \
          PrjTool \
          ProjectManager \
          SessionModule \
          ApplicationWindow

BuildManager.depends = CompileTool
BuildManager.depends = Components

ProjectManager.depends = PrjTool
ProjectManager.depends = Components

SessionModule.depends = BuildManager
SessionModule.depends = ProjectManager
SessionModule.depends = Components

ApplicationWindow.depends = Components
ApplicationWindow.depends = SessionModule
