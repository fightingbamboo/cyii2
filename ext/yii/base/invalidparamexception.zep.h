
extern zend_class_entry *yii_base_invalidparamexception_ce;

ZEPHIR_INIT_CLASS(yii_base_InvalidParamException);

PHP_METHOD(yii_base_InvalidParamException, getName);

ZEPHIR_INIT_FUNCS(yii_base_invalidparamexception_method_entry) {
	PHP_ME(yii_base_InvalidParamException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
