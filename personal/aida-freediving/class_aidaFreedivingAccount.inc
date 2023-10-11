<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2012-2023 FusionDirectory

  Author : Thibault Paul M Dockx

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

class aidaFreedivingAccount extends simplePlugin
{
  protected $displayHeader = TRUE;

  static function plInfo (): array
  {
    return [
      'plShortName' => _('AIDA-Freediving'),
      'plDescription' => _('AIDA-Freediving Plugin'),
      'plObjectType' => ['user'],
      'plObjectClass' => ['fdAidaFreediving'],

      'plProvidedAcls' => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }

  // The main function : information about attributes
  static function getAttributesInfo (): array
  {
    return [
      'aidaAccountInformation' => [
        'name' => _('Student information'),
        'attrs' => [
          new SelectAttribute(
            _('Student current level'), _('Student current level'),
            'fdAidaStudentLevel', FALSE, ['UNCERTIFIED', 'AIDA1', 'AIDA2', 'AIDA3', 'AIDA4'], 'UNCERTIFIED'
          ),
          new BooleanAttribute(
            _('Medical form'), _('Medical form completed'),  'fdAidaStudentMedicalFormCompleted', FALSE, FALSE
          ),
          new BooleanAttribute(
            _('Liability form'), _('Liability form completed'),  'fdAidaStudentLiabilityFormCompleted', FALSE, FALSE
          ),
        ]
      ],
    ];
  }

  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    global $config;
    parent::__construct($dn, $object, $parent, $mainTab);
  }

  protected function shouldSave (): bool
  {
    return parent::shouldSave();
  }

  /*
   * Save method, by interface rule, must remain public
   */
  public function save (): array
  {
    $errors = parent::save();
    return $errors;
  }
}
