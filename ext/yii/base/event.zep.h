
extern zend_class_entry *yii_base_event_ce;

ZEPHIR_INIT_CLASS(yii_base_Event);

PHP_METHOD(yii_base_Event, on);
PHP_METHOD(yii_base_Event, off);
PHP_METHOD(yii_base_Event, offAll);
PHP_METHOD(yii_base_Event, hasHandlers);
PHP_METHOD(yii_base_Event, trigger);
void zephir_init_static_properties_yii_base_Event(TSRMLS_D);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_event_on, 0, 0, 3)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, handler)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, append)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_event_off, 0, 0, 2)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, handler)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_event_hashandlers, 0, 0, 2)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_event_trigger, 0, 0, 2)
	ZEND_ARG_INFO(0, class)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, event)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_base_event_method_entry) {
	PHP_ME(yii_base_Event, on, arginfo_yii_base_event_on, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_base_Event, off, arginfo_yii_base_event_off, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_base_Event, offAll, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_base_Event, hasHandlers, arginfo_yii_base_event_hashandlers, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(yii_base_Event, trigger, arginfo_yii_base_event_trigger, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
