
extern zend_class_entry *yii_base_invalidconfigexception_ce;

ZEPHIR_INIT_CLASS(yii_base_InvalidConfigException);

PHP_METHOD(yii_base_InvalidConfigException, getName);

ZEPHIR_INIT_FUNCS(yii_base_invalidconfigexception_method_entry) {
	PHP_ME(yii_base_InvalidConfigException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
