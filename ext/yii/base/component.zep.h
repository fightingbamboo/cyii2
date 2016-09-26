
extern zend_class_entry *yii_base_component_ce;

ZEPHIR_INIT_CLASS(yii_base_Component);

PHP_METHOD(yii_base_Component, __get);
PHP_METHOD(yii_base_Component, __set);
PHP_METHOD(yii_base_Component, __isset);
PHP_METHOD(yii_base_Component, __unset);
PHP_METHOD(yii_base_Component, __call);
PHP_METHOD(yii_base_Component, __clone);
PHP_METHOD(yii_base_Component, hasProperty);
PHP_METHOD(yii_base_Component, canGetProperty);
PHP_METHOD(yii_base_Component, canSetProperty);
PHP_METHOD(yii_base_Component, hasMethod);
PHP_METHOD(yii_base_Component, behaviors);
PHP_METHOD(yii_base_Component, hasEventHandlers);
PHP_METHOD(yii_base_Component, on);
PHP_METHOD(yii_base_Component, off);
PHP_METHOD(yii_base_Component, trigger);
PHP_METHOD(yii_base_Component, getBehavior);
PHP_METHOD(yii_base_Component, getBehaviors);
PHP_METHOD(yii_base_Component, attachBehavior);
PHP_METHOD(yii_base_Component, attachBehaviors);
PHP_METHOD(yii_base_Component, detachBehavior);
PHP_METHOD(yii_base_Component, detachBehaviors);
PHP_METHOD(yii_base_Component, ensureBehaviors);
PHP_METHOD(yii_base_Component, attachBehaviorInternal);
zend_object_value zephir_init_properties_yii_base_Component(zend_class_entry *class_type TSRMLS_DC);

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component___get, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component___set, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component___isset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component___unset, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component___call, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_ARRAY_INFO(0, params, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_hasproperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkVars)
	ZEND_ARG_INFO(0, checkBehaviors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_cangetproperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkVars)
	ZEND_ARG_INFO(0, checkBehaviors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_cansetproperty, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkVars)
	ZEND_ARG_INFO(0, checkBehaviors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_hasmethod, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, checkBehaviors)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_haseventhandlers, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_on, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, handler)
	ZEND_ARG_INFO(0, data)
	ZEND_ARG_INFO(0, append)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_off, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, handler)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_trigger, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_OBJ_INFO(0, event, yii\\base\\Event, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_getbehavior, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_attachbehavior, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, behavior)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_attachbehaviors, 0, 0, 1)
	ZEND_ARG_ARRAY_INFO(0, behaviors, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_detachbehavior, 0, 0, 1)
	ZEND_ARG_INFO(0, name)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_yii_base_component_attachbehaviorinternal, 0, 0, 2)
	ZEND_ARG_INFO(0, name)
	ZEND_ARG_INFO(0, behavior)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(yii_base_component_method_entry) {
	PHP_ME(yii_base_Component, __get, arginfo_yii_base_component___get, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, __set, arginfo_yii_base_component___set, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, __isset, arginfo_yii_base_component___isset, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, __unset, arginfo_yii_base_component___unset, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, __call, arginfo_yii_base_component___call, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, __clone, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, hasProperty, arginfo_yii_base_component_hasproperty, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, canGetProperty, arginfo_yii_base_component_cangetproperty, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, canSetProperty, arginfo_yii_base_component_cansetproperty, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, hasMethod, arginfo_yii_base_component_hasmethod, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, behaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, hasEventHandlers, arginfo_yii_base_component_haseventhandlers, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, on, arginfo_yii_base_component_on, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, off, arginfo_yii_base_component_off, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, trigger, arginfo_yii_base_component_trigger, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, getBehavior, arginfo_yii_base_component_getbehavior, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, getBehaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, attachBehavior, arginfo_yii_base_component_attachbehavior, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, attachBehaviors, arginfo_yii_base_component_attachbehaviors, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, detachBehavior, arginfo_yii_base_component_detachbehavior, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, detachBehaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, ensureBehaviors, NULL, ZEND_ACC_PUBLIC)
	PHP_ME(yii_base_Component, attachBehaviorInternal, arginfo_yii_base_component_attachbehaviorinternal, ZEND_ACC_PROTECTED)
	PHP_FE_END
};
