# cyii2
extension of yii 2, speed up for it

修改

yii2/framework/di/Container.php

@@ -428,7 +428,7 @@ class Container extends Component
                     $dependencies[] = $param->getDefaultValue();
                 } else {
                     $c = $param->getClass();
-                    $dependencies[] = Instance::of($c === null ? null : $c->getName());
+                    $dependencies[] = $c === null ? [] : Instance::of( $c->getName());
                 }
             }
         }

zephir/Library/CompilerFile.php

@@ -613,7 +613,7 @@ class CompilerFile
                     }
                     $namespace = $topStatement['name'];
                     $this->_namespace = $namespace;
-                    if (!preg_match('/^[A-Z]/', $namespace)) {
+                    if (!preg_match('/^[a-zA-Z]/', $namespace)) {
                         throw new CompilerException("Namespace '" . $namespace . "' must be in camelized-form", $topStatement);
                     }
                     break;
