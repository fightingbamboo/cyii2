<?php
if (!class_exists('HTMLPurifier_Config', false)) {

    class HTMLPurifier_Config
    {
        public static function create($config, $schema = null)
        {
        }
    }
}

if (!class_exists('HTMLPurifier_Lexer', false)) {
    class HTMLPurifier_Lexer
    {
        public static function create($config)
        {
        }
    }

}

if (!class_exists('HTMLPurifier_Generator', false)) {
    class HTMLPurifier_Generator
    {
        public function generateFromTokens($token)
        {

        }
    }

}

if (!class_exists('HTMLPurifier_Generator', false)) {
    class HTMLPurifier_Generator
    {
    }

}
if (!class_exists('HTMLPurifier_Context', false)) {
    class HTMLPurifier_Context
    {
    }

}
