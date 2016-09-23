
extern zend_class_entry *yii_base_actionevent_ce;

ZEPHIR_INIT_CLASS(yii_base_ActionEvent);

PHP_METHOD(yii_base_ActionEvent, __construct);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_actionevent___construct, 0, 0, 1)
	ZEND_ARG_INFO(0, action)
	ZEND_ARG_INFO(0, config)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_base_actionevent_method_entry) {
	PHP_ME(yii_base_ActionEvent, __construct, arginfo_yii_base_actionevent___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE_END
};
