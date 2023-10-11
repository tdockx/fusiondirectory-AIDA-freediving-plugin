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
            _('Medical form'), _('Medical form completed'), 'fdAidaStudentMedicalFormCompleted', FALSE, FALSE
          ),
          new BooleanAttribute(
            _('Liability form'), _('Liability form completed'), 'fdAidaStudentLiabilityFormCompleted', FALSE, FALSE
          ),
        ]
      ],
      'aidaAccountInformationCompletion' => [
        'name' => _('Student information'),
        'attrs' => [
          new BooleanAttribute(
            _('Breath Holding'), _('Breath Holding'),
            'fdAida1CompletionBreathHold', FALSE
          ),
          new BooleanAttribute(
            _('Water session'), _('Water session'),
            'fdAida1CompletionWaterSession', FALSE
          ),
          new BooleanAttribute(
            _('CWT Depth'), _('Student CWT Depth (max 20m)'),
            'fdAida2CWTDepth', FALSE
          ),
        ]
      ],
    ];
  }

  function __construct ($dn = NULL, $object = NULL, $parent = NULL, $mainTab = FALSE)
  {
    global $config;
    parent::__construct($dn, $object, $parent, $mainTab);

    // Management of visibility of some attributes
    $this->setAllAttributesInvisible();
    $this->showProperAttributesForStudentLevel();

    //When changing the level, refresh page by sending post and calling method name sent as string (see class_Attributes).
    $this->attributesAccess['fdAidaStudentLevel']->setSubmitForm('showProperAttributesForStudentLevel');
  }

  // Function allowing to hide or show attributes related to the level of the student
  public function showProperAttributesForStudentLevel () : void
  {
    // Get the student current level
    $aidaStudentLevel = $this->attributesAccess['fdAidaStudentLevel']->getValue();
    //Set all attribute invisible before rendering them visible (Important during the refresh form of student level).
    $this->setAllAttributesInvisible();

    switch($aidaStudentLevel) {
      case 'AIDA1' :
        $this->setAida1AttributesVisible();
        break;

      case 'AIDA2' :
        $this->setAida2AttributesVisible();
        break;

      default :
        $this->setAllAttributesInvisible();
        break;
    }
  }

  // Simply set all attributes invisible
  public function setAllAttributesInvisible () : void
  {
    foreach($this->attributesAccess as $attrObject) {
      $attrObject->setVisible(FALSE);
    }
    // Set mandatory attributes visible
    $this->attributesAccess['fdAidaStudentLevel']->setVisible(TRUE);
    $this->attributesAccess['fdAidaStudentMedicalFormCompleted']->setVisible(TRUE);
    $this->attributesAccess['fdAidaStudentLiabilityFormCompleted']->setVisible(TRUE);
  }

  // Simply set all AIDA 1 completion form attributes visible
  public function setAida1AttributesVisible () : void
  {
    $this->attributesAccess['fdAida1CompletionBreathHold']->setVisible(TRUE);
    $this->attributesAccess['fdAida1CompletionWaterSession']->setVisible(TRUE);
  }
  // Simply set all AIDA 2 completion oform attributes visible
  public function setAida2AttributesVisible () : void
  {
    $this->attributesAccess['fdAida2CWTDepth']->setVisible(TRUE);
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
