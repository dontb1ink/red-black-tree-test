define np
    if $argc != 1
        echo need arg
    else
	p $arg0
        p $arg0.color
	p $arg0.val
	p $arg0.left
	p $arg0.right
    end
end
