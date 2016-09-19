/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */

namespace yii\base;

use yii\BaseYii;
use yii\web\Link;
use yii\web\Linkable;

/**
 * ArrayableTrait provides a common implementation of the [[Arrayable]] interface.
 *
 * ArrayableTrait implements [[toArray()]] by respecting the field definitions as declared
 * in [[fields()]] and [[extraFields()]].
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
class ArrayableTrait
{
    /**
     * Returns the list of fields that should be returned by default by [[toArray()]] when no specific fields are specified.
     *
     * A field is a named element in the returned array by [[toArray()]].
     *
     * This method should return an array of field names or field definitions.
     * If the former, the field name will be treated as an object property name whose value will be used
     * as the field value. If the latter, the array key should be the field name while the array value should be
     * the corresponding field definition which can be either an object property name or a PHP callable
     * returning the corresponding field value. The signature of the callable should be:
     *
     * ```php
     * function ($field, $model) {
     *     // return field value
     * }
     * ```
     *
     * For example, the following code declares four fields:
     *
     * - `email`: the field name is the same as the property name `email`;
     * - `firstName` and `lastName`: the field names are `firstName` and `lastName`, and their
     *   values are obtained from the `first_name` and `last_name` properties;
     * - `fullName`: the field name is `fullName`. Its value is obtained by concatenating `first_name`
     *   and `last_name`.
     *
     * ```php
     * return [
     *     'email',
     *     'firstName' => 'first_name',
     *     'lastName' => 'last_name',
     *     'fullName' => function () {
     *         return $this->first_name . ' ' . $this->last_name;
     *     },
     * ];
     * ```
     *
     * In this method, you may also want to return different lists of fields based on some context
     * information. For example, depending on the privilege of the current application user,
     * you may return different sets of visible fields or filter out some fields.
     *
     * The default implementation of this method returns the public object member variables.
     *
     * @return array the list of field names or field definitions.
     * @see toArray()
     */
    public function fields()
    {
        var fields;
        let fields = array_keys(BaseYii::getObjectVars(this));
        return array_combine(fields, fields);
    }

    /**
     * Returns the list of fields that can be expanded further and returned by [[toArray()]].
     *
     * This method is similar to [[fields()]] except that the list of fields returned
     * by this method are not returned by default by [[toArray()]]. Only when field names
     * to be expanded are explicitly specified when calling [[toArray()]], will their values
     * be exported.
     *
     * The default implementation returns an empty array.
     *
     * You may override this method to return a list of expandable fields based on some context information
     * (e.g. the current application user).
     *
     * @return array the list of expandable field names or field definitions. Please refer
     * to [[fields()]] on the format of the return value.
     * @see toArray()
     * @see fields()
     */
    public function extraFields()
    {
        return [];
    }

    /**
     * Converts the model into an array.
     *
     * This method will first identify which fields to be included in the resulting array by calling [[resolveFields()]].
     * It will then turn the model into an array with these fields. If `$recursive` is true,
     * any embedded objects will also be converted into arrays.
     *
     * If the model implements the [[Linkable]] interface, the resulting array will also have a `_link` element
     * which refers to a list of links as specified by the interface.
     *
     * @param array $fields the fields being requested. If empty, all fields as specified by [[fields()]] will be returned.
     * @param array $expand the additional fields being requested for exporting. Only fields declared in [[extraFields()]]
     * will be considered.
     * @param boolean $recursive whether to recursively return array representation of embedded objects.
     * @return array the array representation of the object
     */
    public function toArray(fields = null, expand = null, recursive = null)
    {
        var data = [], resolve_fields, field, definition;
        let resolve_fields = this->resolveFields(fields, expand);
        for field, definition in resolve_fields {
            if typeof definition == "string" {
                let data[field] = this->{definition};
            }
            else {
                let data[field] = call_user_func(definition, field, $this);
            }
        }

        if this instanceof Linkable {
            let data["_links"] = Link::serialize(this->getLinks());
        }

        return recursive ? $static::toArrayHelper(data) : data;
    }

    public static function toArrayHelper($object, properties = [], boolean recursive = true)
    {
        var key, value, className, name, result;
        if typeof $object == "array" {
            if recursive == true {
                for key, value in $object {
                    if typeof value == "array" || typeof value == "object" {
                        let $object[key] = $static::toArrayHelper(value, properties, true);
                    }
                }
            }
            return $object;
        } else {
            if typeof $object == "object" {
                if count(properties) > 0 {
                    let className = get_class($object);
                    if isset properties[className] && !empty properties[className] {
                        if typeof properties[className] == "array" {
                            let result = [];
                            for key, name in properties[className] {
                                if typeof key == "integer" {
                                    let result[name] = $object->{name};
                                }
                                else {
                                    let result[key] = $static::getValueHelper($object, name);
                                }
                            }
                            if recursive == true {
                                return $static::toArrayHelper(result);
                            }
                            else {
                                return result;
                            }

                        }
                    }
                }

                if $object instanceof "yii\\base\\Arrayable" {
                    let result = $object->toArray();
                }
                else {
                    let result = get_object_vars($object);
                }

                if recursive == true {
                    return $static::toArrayHelper(result);
                }
                else {
                    return result;
                }
            }
            else {
                let result = [],
                    result[] = $object;
                return result;
            }
        }
    }

    /**
         * Retrieves the value of an array element or object property with the given key or property name.
         * If the key does not exist in the array or object, the default value will be returned instead.
         *
         * The key may be specified in a dot format to retrieve the value of a sub-array or the property
         * of an embedded object. In particular, if the key is `x.y.z`, then the returned value would
         * be `$array['x']['y']['z']` or `$array->x->y->z` (if `$array` is an object). If `$array['x']`
         * or `$array->x` is neither an array nor an object, the default value will be returned.
         * Note that if the array already has an element `x.y.z`, then its value will be returned
         * instead of going through the sub-arrays.
         *
         * Below are some usage examples,
         *
         * ~~~
         * // working with array
         * $username = \yii\helpers\ArrayHelper::getValue($_POST, 'username');
         * // working with object
         * $username = \yii\helpers\ArrayHelper::getValue($user, 'username');
         * // working with anonymous function
         * $fullName = \yii\helpers\ArrayHelper::getValue($user, function ($user, $defaultValue) {
         *     return $user->firstName . ' ' . $user->lastName;
         * });
         * // using dot format to retrieve the property of embedded object
         * $street = \yii\helpers\ArrayHelper::getValue($users, 'address.street');
         * ~~~
         *
         * @param array|object $array array or object to extract value from
         * @param string|\Closure $key key name of the array element, or property name of the object,
         * or an anonymous function returning the value. The anonymous function signature should be:
         * `function($array, $defaultValue)`.
         * @param mixed $default the default value to be returned if the specified key does not exist
         * @return mixed the value of the element if found, default value otherwise
         * @throws InvalidParamException if $array is neither an array nor an object.
         */
        public static function getValueHelper($array, key, default_value = null)
        {
            var pos, new_key, temp_key, new_array;
            if typeof key == "object" {
                if key instanceof \Closure {
                    return {key}($array, default_value);
                }
            }

            if typeof key == "string" {
                if typeof $array == "array" && array_key_exists(key, $array) {
                    return $array[key];
                }
                let pos = strrpos(key, ".");
                if typeof pos != "boolean" {
                    let temp_key = substr(key, 0, pos),
                        new_array = $static::getValueHelper($array, temp_key, default_value),
                        new_key = substr(key, pos + 1);
                }
                else {
                    let new_array = $array,
                        new_key = key;
                }

                if typeof new_array == "object" {
                    return new_array->{new_key};
                } else {
                    if typeof new_array == "array" {
                        if array_key_exists(new_key, new_array) {
                            return new_array[new_key];
                        }
                        else {
                            return default_value;
                        }
                    }
                    else {
                        return default_value;
                    }
                }
            }
        }

    /**
     * Determines which fields can be returned by [[toArray()]].
     * This method will check the requested fields against those declared in [[fields()]] and [[extraFields()]]
     * to determine which fields can be returned.
     * @param array $fields the fields being requested for exporting
     * @param array $expand the additional fields being requested for exporting
     * @return array the list of fields to be exported. The array keys are the field names, and the array values
     * are the corresponding object property names or PHP callables returning the field values.
     */
    protected function resolveFields(array fields, array expand)
    {
        var result = [], this_fields, field, definition, extra_fields, extra_field, extra_definition;
        let this_fields = this->fields();

        for field, definition in this_fields {
            if typeof field == "integer" {
                let field = definition;
            }
            if count(fields) == 0 || in_array(field, fields, true) {
                let result[field] = definition;
            }
        }

        if count(expand) == 0 {
            return result;
        }
        let extra_fields = this->extraFields();
        for extra_field, extra_definition in extra_fields {

            if typeof extra_field == "integer" {
                let extra_field = extra_definition;
            }
            if in_array(extra_field, expand, true) {
                let result[extra_field] = extra_definition;
            }
        }

        return result;
    }
}
