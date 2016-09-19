<?php
/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */

namespace yii\helpers;

use yii\BaseYii;

/**
 * BaseStringHelper provides concrete implementation for [[StringHelper]].
 *
 * Do not use BaseStringHelper. Use [[StringHelper]] instead.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @author Alex Makarov <sam@rmcreative.ru>
 * @since 2.0
 */
class BaseStringHelper
{
    /**
     * Returns the number of bytes in the given string.
     * This method ensures the string is treated as a byte array by using `mb_strlen()`.
     * @param string $string the string being measured for length
     * @return integer the number of bytes in the given string.
     */
    public static function byteLength(string str)
    {
        return mb_strlen(str, "8bit");
    }

    /**
     * Returns the portion of string specified by the start and length parameters.
     * This method ensures the string is treated as a byte array by using `mb_substr()`.
     * @param string $string the input string. Must be one character or longer.
     * @param integer $start the starting position
     * @param integer $length the desired portion length
     * @return string the extracted part of string, or FALSE on failure or an empty string.
     * @see http://www.php.net/manual/en/function.substr.php
     */
    public static function byteSubstr(string str, int start, int length)
    {
        return mb_substr(str, start, length, "8bit");
    }

    /**
     * Returns the trailing name component of a path.
     * This method is similar to the php function `basename()` except that it will
     * treat both \ and / as directory separators, independent of the operating system.
     * This method was mainly created to work on php namespaces. When working with real
     * file paths, php's `basename()` should work fine for you.
     * Note: this method is not aware of the actual filesystem, or path components such as "..".
     *
     * @param string $path A path string.
     * @param string $suffix If the name component ends in suffix this will also be cut off.
     * @return string the trailing name component of the given path.
     * @see http://www.php.net/manual/en/function.basename.php
     */
    public static function basename(path, string suffix = "")
    {
        var len, negative_len, pos;

        let len = mb_strlen(suffix);
        if len > 0 {
            let negative_len = len * -1;
            if mb_substr(path, negative_len) == suffix {
                let path = mb_substr(path, 0, negative_len);
            }
        }
        let path = str_replace("\\", "/", path),
            path = rtrim(path, "/\\"),
            pos = mb_strrpos(path, "/");

        if typeof pos != "boolean" {
            return mb_substr(path, pos + 1);
        }

        return path;
    }

    /**
     * Returns parent directory's path.
     * This method is similar to `dirname()` except that it will treat
     * both \ and / as directory separators, independent of the operating system.
     *
     * @param string $path A path string.
     * @return string the parent directory's path.
     * @see http://www.php.net/manual/en/function.basename.php
     */
    public static function dirname(path)
    {
        var pos;
        let pos = mb_strrpos(str_replace("\\", "/", path), "/");
        if typeof pos != "boolean" {
            return mb_substr(path, 0, pos);
        } else {
            return "";
        }
    }

    /**
     * Truncates a string to the number of characters specified.
     *
     * @param string $string The string to truncate.
     * @param integer $length How many characters from original string to include into truncated string.
     * @param string $suffix String to append to the end of truncated string.
     * @param string $encoding The charset to use, defaults to charset currently used by application.
     * @return string the truncated string.
     */
    public static function truncate(string str, length, suffix = "...", encoding = null)
    {
        if typeof encoding == "null" {
            let encoding = BaseYii::$app->charset;
        }
        if mb_strlen(str, encoding) > length {
            return trim(mb_substr(str, 0, length, encoding)) . suffix;
        } else {
            return str;
        }
    }

    /**
     * Truncates a string to the number of words specified.
     *
     * @param string $string The string to truncate.
     * @param integer $count How many words from original string to include into truncated string.
     * @param string $suffix String to append to the end of truncated string.
     * @return string the truncated string.
     */
    public static function truncateWords(string str, count_num, suffix = "...")
    {
        var words, current_words, slice, temp_words, retval;
        let str = trim(str),
            words = preg_split("/(\\s+)/u", str , null, PREG_SPLIT_DELIM_CAPTURE);

        let current_words = count(words) / 2,
            slice = count_num * 2 - 1;


        if current_words > count_num {
            let temp_words = array_slice(words, 0, slice),
                retval = implode("", temp_words),
                retval = retval . suffix;
            return retval;
        } else {
            return str;
        }
    }


    /**
     * Check if given string starts with specified substring.
     * Binary and multibyte safe.
     *
     * @param string $string Input string
     * @param string $with Part to search
     * @param boolean $caseSensitive Case sensitive search. Default is true.
     * @return boolean Returns true if first input starts with second input, false otherwise
     */
    public static function startsWith($string, with, caseSensitive = true)
    {
        var bytes;
        let bytes = static::byteLength(with);
        if !bytes {
            return true;
        }
        if caseSensitive {
            return strncmp($string, with, bytes) === 0;
        } else {
            return mb_strtolower(mb_substr($string, 0, bytes, '8bit'), BaseYii::$app->charset) === mb_strtolower(with, BaseYii::$app->charset);
        }
    }

    /**
     * Check if given string ends with specified substring.
     * Binary and multibyte safe.
     *
     * @param string $string
     * @param string $with
     * @param boolean $caseSensitive Case sensitive search. Default is true.
     * @return boolean Returns true if first input ends with second input, false otherwise
     */
    public static function endsWith($string, with, caseSensitive = true)
    {
        var bytes;
        let bytes = static::byteLength(with);
        if !bytes {
            return true;
        }
        if caseSensitive {
            // Warning check, see http://php.net/manual/en/function.substr-compare.php#refsect1-function.substr-compare-returnvalues
            if static::byteLength($string) < bytes {
                return false;
            }
            return substr_compare($string, with, -bytes, bytes) === 0;
        } else {
            return mb_strtolower(mb_substr($string, -bytes, mb_strlen($string, '8bit'), '8bit'), BaseYii::$app->charset) === mb_strtolower(with, BaseYii::$app->charset);
        }
    }

    /**
     * Explodes string into array, optionally trims values and skips empty ones
     *
     * @param string $string String to be exploded.
     * @param string $delimiter Delimiter. Default is ','.
     * @param mixed $trim Whether to trim each element. Can be:
     *   - boolean - to trim normally;
     *   - string - custom characters to trim. Will be passed as a second argument to `trim()` function.
     *   - callable - will be called for each value instead of trim. Takes the only argument - value.
     * @param boolean $skipEmpty Whether to skip empty strings between delimiters. Default is false.
     * @return array
     * @since 2.0.4
     */
    public static function explode(string str, string delimiter = ',', trim = true, skipEmpty = false)
    {
        var result;
        let result = explode(delimiter, str);
        if trim {
            if trim === true {
                let trim = "trim";
            } elseif !is_callable(trim) {
                let trim = function (v) use (trim) {
                    return trim(v, trim);
                };
            }
            let result = array_map(trim, result);
        }
        if skipEmpty {
            // Wrapped with array_values to make array keys sequential after empty values removing
            let result = array_values(array_filter(result, function (value) {
                return value !== '';
            }));
        }
        return result;
    }

    /**
     * Counts words in a string
     * @since 2.0.8
     *
     * @param string $string
     * @return integer
     */
    public static function countWords(string str)
    {
        return count(preg_split('/\s+/u', str, null, PREG_SPLIT_NO_EMPTY));
    }
}
