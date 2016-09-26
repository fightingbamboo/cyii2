
extern zend_class_entry *yii_base_viewcontextinterface_ce;

ZEPHIR_INIT_CLASS(yii_base_ViewContextInterface);

ZEPHIR_INIT_FUNCS(yii_base_viewcontextinterface_method_entry) {
	PHP_ABSTRACT_ME(yii_base_ViewContextInterface, getViewPath, NULL)
	PHP_FE_END
};
