
extern zend_class_entry *yii_base_unknownpropertyexception_ce;

ZEPHIR_INIT_CLASS(yii_base_UnknownPropertyException);

PHP_METHOD(yii_base_UnknownPropertyException, getName);

ZEPHIR_INIT_FUNCS(yii_base_unknownpropertyexception_method_entry) {
	PHP_ME(yii_base_UnknownPropertyException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
