# Main build file for project.
# This just includes the subdirectories Sources (with sources to be tested), and Test
# (with the test suite). It also takes care of generating the test report.

TEMPLATE = subdirs

CONFIG += c++11 release

SUBDIRS = Application Sources Test

Test.depends = Sources
Application.depends = Sources

# Generate HTML report for unit tests when running "make check"
check.commands += xsltproc Test/report.xsl Test/testresults.xml > testresults.html
