
extern zend_class_entry *yii_base_unknownmethodexception_ce;

ZEPHIR_INIT_CLASS(yii_base_UnknownMethodException);

PHP_METHOD(yii_base_UnknownMethodException, getName);

ZEPHIR_INIT_FUNCS(yii_base_unknownmethodexception_method_entry) {
	PHP_ME(yii_base_UnknownMethodException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
