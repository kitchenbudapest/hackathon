/* INFO **
** INFO */


(function ()
{
    'use strict';

    var i = 0;
    function jprint(arg)
    {
        print('[' + (i++).toString() + '] js:', arg);
    }
    var t = new T('hello');

    jprint(t);
    jprint(T);
    jprint(T.prototype);
})();


(function ()
{
    'use strict';

    var t1 = new T('hello'),
        t2 = new T('world');

    print(t1, t2);
})();


// (function ()
// {
//     'use strict';
//
//     function MyT()
//     {
//         T.call(this);
//     }
//
//     MyT.prototype.on_call = function ()
//     {
//         print('MyT.on_call()');
//     };
//
//     print(new MyT('xxx'));
//
// })();
