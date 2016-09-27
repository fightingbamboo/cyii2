<?php
if (!class_exists('Yii', false)) {

    class Yii
    {
        public static $classMap = [];
        public static $app;

        public static $aliases;

        public static $container;

        public static function getVersion()
        {
        }

        public static function getAlias($alias, $throwException = true)
        {
        }

        public static function getRootAlias($alias)
        {
        }

        public static function setAlias($alias, $path)
        {
        }

        public static function autoload($className)
        {
        }


        public static function createObject($type, array $params = [])
        {
        }

        private static $_logger;


        public static function getLogger()
        {
        }

        public static function setLogger($logger)
        {
        }

        public static function trace($message, $category = 'application')
        {
        }

        public static function error($message, $category = 'application')
        {
        }

        public static function warning($message, $category = 'application')
        {

        }


        public static function info($message, $category = 'application')
        {
        }

        public static function beginProfile($token, $category = 'application')
        {
        }

        public static function endProfile($token, $category = 'application')
        {
        }

        public static function powered()
        {
        }

        public static function t($category, $message, $params = [], $language = null)
        {

        }

        public static function configure($object, $properties)
        {

        }

        public static function getObjectVars($object)
        {

        }
    }
}