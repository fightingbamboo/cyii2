
extern zend_class_entry *yii_base_viewnotfoundexception_ce;

ZEPHIR_INIT_CLASS(yii_base_ViewNotFoundException);

PHP_METHOD(yii_base_ViewNotFoundException, getName);

ZEPHIR_INIT_FUNCS(yii_base_viewnotfoundexception_method_entry) {
	PHP_ME(yii_base_ViewNotFoundException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
