/**
 * @link http://www.yiiframework.com/
 * @copyright Copyright (c) 2008 Yii Software LLC
 * @license http://www.yiiframework.com/license/
 */
namespace yii\base;

/**
 * Event is the base class for all event classes.
 *
 * It encapsulates the parameters associated with an event.
 * The [[sender]] property describes who raises the event.
 * And the [[handled]] property indicates if the event is handled.
 * If an event handler sets [[handled]] to be `true`, the rest of the
 * uninvoked handlers will no longer be called to handle the event.
 *
 * Additionally, when attaching an event handler, extra data may be passed
 * and be available via the [[data]] property when the event handler is invoked.
 *
 * @author Qiang Xue <qiang.xue@gmail.com>
 * @since 2.0
 */
class Event extends \yii\base\Object
{
    /**
     * @var string the event name. This property is set by [[Component::trigger()]] and [[trigger()]].
     * Event handlers may use this property to check what event it is handling.
     */
    public name;
    /**
     * @var object the sender of this event. If not set, this property will be
     * set as the object whose `trigger()` method is called.
     * This property may also be a `null` when this event is a
     * class-level event which is triggered in a static context.
     */
    public sender;
    /**
     * @var boolean whether the event is handled. Defaults to `false`.
     * When a handler sets this to be `true`, the event processing will stop and
     * ignore the rest of the uninvoked event handlers.
     */
    public handled = false;
    /**
     * @var mixed the data that is passed to [[Component::on()]] when attaching an event handler.
     * Note that this varies according to which event handler is currently executing.
     */
    public data;
    /**
     * @var array contains all globally registered event handlers.
     */
    private static _events = [];
    /**
     * Attaches an event handler to a class-level event.
     *
     * When a class-level event is triggered, event handlers attached
     * to that class and all parent classes will be invoked.
     *
     * For example, the following code attaches an event handler to `ActiveRecord`'s
     * `afterInsert` event:
     *
     * ```php
     * Event::on(ActiveRecord::className(), ActiveRecord::EVENT_AFTER_INSERT, function ($event) {
     *     Yii::trace(get_class($event->sender) . ' is inserted.');
     * });
     * ```
     *
     * The handler will be invoked for EVERY successful ActiveRecord insertion.
     *
     * For more details about how to declare an event handler, please refer to [[Component::on()]].
     *
     * @param string $class the fully qualified class name to which the event handler needs to attach.
     * @param string $name the event name.
     * @param callable $handler the event handler.
     * @param mixed $data the data to be passed to the event handler when the event is triggered.
     * When the event handler is invoked, this data can be accessed via [[Event::data]].
     * @param boolean $append whether to append new event handler to the end of the existing
     * handler list. If `false`, the new handler will be inserted at the beginning of the existing
     * handler list.
     * @see off()
     */
    public static function on(string classs, string name, handler, data = null, boolean append = true) -> void
    {
        var tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125;
    
        let classs =  ltrim(classs, "\\");
        if append || ( !isset self::_events[name] || !isset self::_events[name][classs] || empty(self::_events[name][classs])) {
            let self::_events[name][classs][] =  [handler, data];
        } else {
            let tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125 = [handler, data];
            array_unshift(self::_events[name][classs], tmpArray3b96bb5d49aa4e738ab1b36c1e0a9125);
        }
    }
    
    /**
     * Detaches an event handler from a class-level event.
     *
     * This method is the opposite of [[on()]].
     *
     * @param string $class the fully qualified class name from which the event handler needs to be detached.
     * @param string $name the event name.
     * @param callable $handler the event handler to be removed.
     * If it is `null`, all handlers attached to the named event will be removed.
     * @return boolean whether a handler is found and detached.
     * @see on()
     */
    public static function off(string classs, string name, handler = null)
    {
        var removed, i, event;
    
        let classs =  ltrim(classs, "\\");
        if !isset self::_events[name] || !isset self::_events[name][classs] || empty(self::_events[name][classs]) {
            return false;
        }
        if handler === null {
            unset self::_events[name][classs];
            
            return true;
        } else {
            let removed =  false;
            for i, event in self::_events[name][classs] {
                if event[0] === handler {
                    unset self::_events[name][classs][i];
                    
                    let removed =  true;
                }
            }
            if removed {
                let self::_events[name][classs] =  array_values(self::_events[name][classs]);
            }
            return removed;
        }
    }
    
    /**
     * Detaches all registered class-level event handlers.
     * @see on()
     * @see off()
     * @since 2.0.10
     */
    public static function offAll() -> void
    {
        let self::_events =  [];
    }
    
    /**
     * Returns a value indicating whether there is any handler attached to the specified class-level event.
     * Note that this method will also check all parent classes to see if there is any handler attached
     * to the named event.
     * @param string|object $class the object or the fully qualified class name specifying the class-level event.
     * @param string $name the event name.
     * @return boolean whether there is any handler attached to the event.
     */
    public static function hasHandlers(classs, string name) -> boolean
    {
        var classes, tmpArray9613f42f8264d80e17bfc80cc7a471fb;
    
        if !isset self::_events[name] || empty(self::_events[name]) {
            return false;
        }
        if is_object(classs) {
            let classs =  get_class(classs);
        } else {
            let classs =  ltrim(classs, "\\");
        }
        let tmpArray9613f42f8264d80e17bfc80cc7a471fb = [classs];
        let classes =  array_merge(tmpArray9613f42f8264d80e17bfc80cc7a471fb, class_parents(classs, true), class_implements(classs, true));
        for classs in classes {
            if  isset self::_events[name][classs] && !empty(self::_events[name][classs]) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Triggers a class-level event.
     * This method will cause invocation of event handlers that are attached to the named event
     * for the specified class and all its parent classes.
     * @param string|object $class the object or the fully qualified class name specifying the class-level event.
     * @param string $name the event name.
     * @param Event $event the event parameter. If not set, a default [[Event]] object will be created.
     */
    public static function trigger(classs, string name, <Event> event = null)
    {
        var classes, tmpArray94fd3581f8118e54e2778c97fdb99a2e, handler;
    
        if !isset self::_events[name] || empty(self::_events[name]) {
            return;
        }
        if event === null {
            let event =  new static();
        }
        let event->handled =  false;
        let event->name = name;
        if is_object(classs) {
            if event->sender === null {
                let event->sender = classs;
            }
            let classs =  get_class(classs);
        } else {
            let classs =  ltrim(classs, "\\");
        }
        let tmpArray94fd3581f8118e54e2778c97fdb99a2e = [classs];
        let classes =  array_merge(tmpArray94fd3581f8118e54e2778c97fdb99a2e, class_parents(classs, true), class_implements(classs, true));
        for classs in classes {
            if  isset self::_events[name][classs] && !empty(self::_events[name][classs]) {
                for handler in self::_events[name][classs] {
                    let event->data = handler[1];
                    call_user_func(handler[0], event);
                    if event->handled {
                        return;
                    }
                }
            }
        }
    }

}