define np
    if $argc != 1
        echo need arg
    else
        echo this left right parent color val\n
        p $arg0
        p $arg0.left
        p $arg0.right
        p $arg0.parent
        p $arg0.color
        p $arg0->get_val()
    end
end
