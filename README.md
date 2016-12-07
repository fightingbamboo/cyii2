# cyii2
##extension of yii 2, speed up for it

###安装工具
* ./vendor/phalcon/zephir/README.md 根据文档安装zephir和php扩展开发 所需的库

* ./vendor/bin/zephir generate 生成代码
* ./vendor/bin/zephir build 编译代码 生成扩展so文件
* 开启扩展并重新启动php进程即可启用该cyii2扩展以加速yii2框架执行

###phpunit run test
* ./vendor/bin/phpunit --group=*  example:base,di,web,mysql

###库修改

#### ./yii2/framework/di/Container.php

```php
@@ -426,6 +426,8 @@ class Container extends Component
             foreach ($constructor->getParameters() as $param) {
                 if ($param->isDefaultValueAvailable()) {
                     $dependencies[] = $param->getDefaultValue();
+                } elseif ($param->getName() == "config") {
+                    $dependencies[] = [];
                 } else {
                     $c = $param->getClass();
                     $dependencies[] = Instance::of($c === null ? null : $c->getName());
@@ -540,6 +542,8 @@ class Container extends Component
                     } catch (NotInstantiableException $e) {
                         if ($param->isDefaultValueAvailable()) {
                             $args[] = $param->getDefaultValue();
+                        } elseif ($param->getName() == "config") {
+                            $dependencies[] = [];
                         } else {
                             throw $e;
                         }
@@ -553,6 +557,8 @@ class Container extends Component
                 $args[] = array_shift($params);
             } elseif ($param->isDefaultValueAvailable()) {
                 $args[] = $param->getDefaultValue();
+            } elseif ($name == "config") {
+                $args[] = [];
             } elseif (!$param->isOptional()) {
                 $funcName = $reflection->getName();
                 throw new InvalidConfigException("Missing required parameter \"$name\" when calling \"$funcName\".");
```
#### ./vendor/phalcon/zephir/Library/CompilerFile.php

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
###性能
* 硬件 mac book pro 2016
* 测试代码 https://github.com/yiisoft/yii2-app-benchmark
* 命令 ab -c 4 -n 5000 http://127.0.0.1:88/yii-benchmark/
* 运行5次取最高值
* cyii2 Requests per second:    478.08 [#/sec] (mean) 
* yii2 Requests per second:     408.08 [#/sec] (mean) 

###已存在的问题
