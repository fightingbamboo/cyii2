# cyii2
##extension of yii 2, speed up for it

###安装工具
####./vendor/phalcon/zephir/README.md 根据文档安装zephir和php扩展开发 所需的库

####./vendor/bin/zephir generate 生成代码
####./vendor/bin/zephir build 编译代码 生成扩展so文件
####开启扩展并重新启动php进程即可启用该cyii2扩展以加速yii2框架执行

###phpunit run test
####./vendor/bin/phpunit --group=*  example:base,di,web,mysql

###库修改

####./yii2/framework/di/Container.php

```php
@@ -428,7 +428,7 @@ class Container extends Component
                     $dependencies[] = $param->getDefaultValue();
                 } else {
                     $c = $param->getClass();
-                    $dependencies[] = Instance::of($c === null ? null : $c->getName());
+                    $dependencies[] = $c === null ? [] : Instance::of( $c->getName());
                 }
             }
         }
```
####./vendor/phalcon/zephir/Library/CompilerFile.php

```php
@@ -613,7 +613,7 @@ class CompilerFile
                     }
                     $namespace = $topStatement['name'];
                     $this->_namespace = $namespace;
-                    if (!preg_match('/^[A-Z]/', $namespace)) {
+                    if (!preg_match('/^[a-zA-Z]/', $namespace)) {
                         throw new CompilerException("Namespace '" . $namespace . "' must be in camelized-form", $topStatement);
                     }
                     break;
```
###已存在的问题
