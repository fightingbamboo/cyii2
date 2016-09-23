
extern zend_class_entry *yii_base_invalidcallexception_ce;

ZEPHIR_INIT_CLASS(yii_base_InvalidCallException);

PHP_METHOD(yii_base_InvalidCallException, getName);

ZEPHIR_INIT_FUNCS(yii_base_invalidcallexception_method_entry) {
	PHP_ME(yii_base_InvalidCallException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
