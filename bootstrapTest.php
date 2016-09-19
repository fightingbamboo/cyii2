<?php

ini_set('zend.enable_gc',0);

// ensure we get report on all possible php errors
error_reporting(-1);

define('YII_ENABLE_ERROR_HANDLER', false);
define('YII_DEBUG', true);
$_SERVER['SCRIPT_NAME'] = '/' . __DIR__;
$_SERVER['SCRIPT_FILENAME'] = __FILE__;

// require composer autoloader if available
$composerAutoload = __DIR__ . '/vendor/autoload.php';
if (is_file($composerAutoload)) {
    require_once($composerAutoload);
} else {
    require_once(__DIR__ . '/../../autoload.php');
}

require_once(__DIR__ . '/CYii.php');

Yii::setAlias('@yiiunit', __DIR__."/yii2/tests");

require_once(__DIR__ . '/yii2/tests/TestCase.php');
