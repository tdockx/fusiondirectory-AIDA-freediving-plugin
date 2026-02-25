# fusiondirectory-AIDA-freediving-plugin

A plugin for FusionDirectory allowing to register AIDA freedivers students and follow their skills requirements, administrative documents and booked trainning dates.

The plugin required version 1.4 from FusionDirectory.
Link : https://gitlab.fusiondirectory.org

Installation
============

1. Clone this repo
2. execute the following CLI :
    - fusiondirectory-plugin-manager --install-plugin /path/to/parent/
    - fusiondirectory-schema-manager --insert-schema /usr/share/fusiondirectory/contrib/openldap/aida-freediving-fd.schema
    - fusiondirectory-configuration-manager --update-cache
3. Login to your FusionDirectory instance.
4. Click on a user and enable the tab AidaFreediving.
5. OPTIONAL : Configure the plugin by heading to Configuration Menu.

NOTE:
====

The installation guidelines and this plugin was only tested under DEBIAN 11.  
It should work on any supported distribution of FusionDirectory but the installation paths might differs.

_Changelog.md will be added later on_  
In format of month/day/year   
- 10/11/23 - Added All levels of AIDA + UNCERTIFIED. 
- 10/11/23 - Added Completion form of AIDA 1 and AIDA 2.
- 10/11/23 - Added Possibility to manage official documents (Liability / Medical).
- 10/11/23 - Added Possibility to manage schedule. 'Start', 'Next'  and 'End' training / coaching date. 
- 10/11/23 - Added Possibility to set a status on Exam (if required), and if student is already certified for selected level.
- 02/25/26 - Adding simple Confined water 1/2 and Open Water 1/2/3/4 for simpler tracking if required. Theory 1/2/3 as well.
