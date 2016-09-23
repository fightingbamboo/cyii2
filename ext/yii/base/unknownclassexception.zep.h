
extern zend_class_entry *yii_base_unknownclassexception_ce;

ZEPHIR_INIT_CLASS(yii_base_UnknownClassException);

PHP_METHOD(yii_base_UnknownClassException, getName);

ZEPHIR_INIT_FUNCS(yii_base_unknownclassexception_method_entry) {
	PHP_ME(yii_base_UnknownClassException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
