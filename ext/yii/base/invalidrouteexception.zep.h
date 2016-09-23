
extern zend_class_entry *yii_base_invalidrouteexception_ce;

ZEPHIR_INIT_CLASS(yii_base_InvalidRouteException);

PHP_METHOD(yii_base_InvalidRouteException, getName);

ZEPHIR_INIT_FUNCS(yii_base_invalidrouteexception_method_entry) {
	PHP_ME(yii_base_InvalidRouteException, getName, NULL, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
