
extern zend_class_entry *yii_log_logger_ce;

ZEPHIR_INIT_CLASS(yii_log_Logger);

PHP_METHOD(yii_log_Logger, init);
PHP_METHOD(yii_log_Logger, log);
PHP_METHOD(yii_log_Logger, flush);
PHP_METHOD(yii_log_Logger, getElapsedTime);
PHP_METHOD(yii_log_Logger, getProfiling);
PHP_METHOD(yii_log_Logger, getDbProfiling);
PHP_METHOD(yii_log_Logger, calculateTimings);
PHP_METHOD(yii_log_Logger, getLevelName);
zend_object_value zephir_init_properties_yii_log_Logger(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_log_logger_log, 0, 0, 2)
	ZEND_ARG_INFO(0, message)
	ZEND_ARG_INFO(0, level)
	ZEND_ARG_INFO(0, category)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_log_logger_flush, 0, 0, 0)
	ZEND_ARG_INFO(0, isFinal)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_log_logger_getprofiling, 0, 0, 0)
	ZEND_ARG_INFO(0, categories)
	ZEND_ARG_INFO(0, excludeCategories)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_log_logger_calculatetimings, 0, 0, 1)
	ZEND_ARG_INFO(0, messages)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_log_logger_getlevelname, 0, 0, 1)
	ZEND_ARG_INFO(0, level)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_log_logger_method_entry) {
	PHP_ME(yii_log_Logger, init, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, log, arginfo_yii_log_logger_log, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, flush, arginfo_yii_log_logger_flush, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, getElapsedTime, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, getProfiling, arginfo_yii_log_logger_getprofiling, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, getDbProfiling, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, calculateTimings, arginfo_yii_log_logger_calculatetimings, ZEND_ACC_PUBLIC)
	PHP_ME(yii_log_Logger, getLevelName, arginfo_yii_log_logger_getlevelname, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
