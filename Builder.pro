TEMPLATE = subdirs

CONFIG += ordered

# Add the subdirectories
SUBDIRS += Plugins \
           Main \
           Tests

# Define dependencies
Main.depends = Plugins

# AICI DEPENDENTELE.separate pentru SUBFOLDER-ele din TESTE
Tests.BuildManagerTests.depends = Plugins
Tests.ProjectManagerTests.depends = Plugins
