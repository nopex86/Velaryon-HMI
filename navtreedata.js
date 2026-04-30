/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Velaryon", "index.html", [
    [ "SDD — Software Design Document", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html", [
      [ "Velaryon V3", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md1", [
        [ "Vue d'ensemble de l'architecture", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md3", [
          [ "1.1 Pattern architectural", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md4", null ],
          [ "1.2 Décomposition en threads", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md5", null ]
        ] ],
        [ "Low-Level Requirements", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md7", [
          [ "2.1 Sous-système UDP", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md8", null ],
          [ "2.2 Ring Buffer", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md9", null ],
          [ "2.3 BdfWriter", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md10", null ],
          [ "2.4 Décimation UI", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md11", null ],
          [ "2.5 Arrêt d'urgence", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md12", null ]
        ] ],
        [ "Décisions de conception", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md14", [
          [ "3.1 Choix du ring buffer SPSC lock-free", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md15", null ],
          [ "3.2 Choix de Qt comme framework", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md16", null ]
        ] ],
        [ "Diagrammes", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md18", [
          [ "4.1 Flux de données", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md19", null ]
        ] ],
        [ "Matrice de traçabilité", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2sdd_2SoftwareDesignDocument.html#autotoc_md21", null ]
      ] ]
    ] ],
    [ "SRS — Software Requirements Specification", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html", [
      [ "Velaryon V3", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md23", [
        [ "Objet et domaine d'application", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md25", [
          [ "1.1 Objet", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md26", null ],
          [ "1.2 Périmètre", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md27", null ],
          [ "1.3 Documents de référence", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md28", null ]
        ] ],
        [ "Exigences générales", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md30", [
          [ "2.1 Exigences de performance", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md31", null ],
          [ "2.2 Exigences de sécurité", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md32", null ]
        ] ],
        [ "Exigences fonctionnelles", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md34", [
          [ "3.1 Acquisition de données", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md35", null ],
          [ "3.2 Logging", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md36", null ],
          [ "3.3 Interface graphique", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md37", null ],
          [ "3.4 Commande des actionneurs", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md38", null ],
          [ "3.5 TVC", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md39", null ]
        ] ],
        [ "Exigences d'interface", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md41", [
          [ "4.1 Interface réseau", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md42", null ],
          [ "4.2 Interface opérateur", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md43", null ]
        ] ],
        [ "Exigences de fiabilité et maintenance", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md45", null ],
        [ "Exigences de non-régression", "md__2home_2runner_2work_2Velaryon-HMI_2Velaryon-HMI_2docs_2srs_2SoftwareRequirementSpecification.html#autotoc_md47", null ]
      ] ]
    ] ],
    [ "Topics", "topics.html", "topics" ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Enumerations", "functions_enum.html", null ],
        [ "Enumerator", "functions_eval.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", null ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"ActuatorControlWidget_8cpp.html",
"classAckBB.html",
"classPlotViewModel.html#a1cf1c30c7d5d9ba0635ebff8166194b2",
"classTimer.html#a44c9208d316a5d99174a7d04349f6bc8",
"functions_vars_b.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';