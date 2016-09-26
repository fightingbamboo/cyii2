
extern zend_class_entry *yii_base_arrayable_ce;

ZEPHIR_INIT_CLASS(yii_base_Arrayable);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_arrayable_toarray, 0, 0, 0)
	ZEND_ARG_ARRAY_INFO(0, fields, 1)
	ZEND_ARG_ARRAY_INFO(0, expand, 1)
	ZEND_ARG_INFO(0, recursive)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_base_arrayable_method_entry) {
	PHP_ABSTRACT_ME(yii_base_Arrayable, fields, NULL)
	PHP_ABSTRACT_ME(yii_base_Arrayable, extraFields, NULL)
	PHP_ABSTRACT_ME(yii_base_Arrayable, toArray, arginfo_yii_base_arrayable_toarray)
	PHP_FE_END
};
