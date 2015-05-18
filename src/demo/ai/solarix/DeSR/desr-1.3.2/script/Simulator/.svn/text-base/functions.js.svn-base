function Stack(name) {
    var stack;

    this.stack = [];
    this.id = name;

    this.topToken = function(n) {
        return this.top(n).getRoot().children[0];
    }

    this.updateAll = function(label, id) {
        for (var i in this.stack) {
            var tree = this.stack[i];
            this.treeUpdate(tree.getRoot().children[0], label, id);
            tree.draw();
        }
    }
    
    this.updateTop = function(label, id) {
        this.treeUpdate(this.topToken(), label, id);
        itree = this.top().draw();
    }

    this.treeUpdate = function(node, label, id) {
        if (node.id == id) {
            node.data.updateLabel(label);
            node.label = node.data.label;
            return true;
        }
        for (var i in node.children) {
            var child = node.children[i];
            if (this.treeUpdate(child, label, id))
                return true;
        }
        return false; 	// not found
    }

    this.clear = function() {
        // clear the HTML stack
        var ni = document.getElementById(this.id);
        for (var i in this.stack)
            ni.removeChild(this.stack[i].getEl());
        this.stack = [];
    }

    this.size = function() {
        return this.stack.length;
    }

    // move the front of queue to top
    this.move = function(queue) {
        var tv = queue.top();
        var nextElement = queue.pop();
        var ni = document.getElementById(this.id);
        ni.appendChild(nextElement);
        this.push(tv);
    }

    this.pushElement = function(element, DOM_element) {
        var ni = document.getElementById(this.id);
        var clonedElement = DOM_element.cloneNode(true);
        ni.appendChild(clonedElement);
        this.push(element);
    }

    this.pushToken = function(token) {
        // create the element
        var element = document.createElement('td');
        element.setAttribute('class', 'stack');
        element.setAttribute('className', 'stack'); // IE bug
        var ni = document.getElementById(this.id);
        ni.appendChild(element);

        // create the TreeView
        var tv = new YAHOO.widget.TreeView(element); // shares property id with element
        var labeledText = new LabeledText(token.data.originalLabel);
        if (token.data.predicate != null)
            labeledText.predicate = token.data.predicate;
        var newToken = new YAHOO.widget.TextNode(labeledText, tv.getRoot(), true);
        newToken.id = token.id;
        newToken.labelStyle = 'textNode';
        this.stack.push(tv);
        tv.draw();
    }
    
    this.push = function(treeView) {
        this.stack.push(treeView);
    }

    this.topElement = function() {
        var d = document.getElementById(this.id);
        var child = d.lastChild;
        return child;
    }

    this.top = function(n) {
        if (!n) n = 1;
        return this.stack[this.size() - n];
    }

    this.pop = function() {
        var d = document.getElementById(this.id);
        var child = d.lastChild;
        d.removeChild(child);
        this.stack.pop();
        return child;
    }

    this.remove = function(n) {
        var d = document.getElementById(this.id);
        var children = d.childNodes;
        var child = children.item(children.length - n);
        d.removeChild(child);
        this.stack.splice(this.stack.length - n, 1);
        return child;
    }

}


function LabeledText(text) {
//function LabeledText(oLabel, oParent, oExpanded) {
//    this.inheritFrom = YAHOO.widget.TextNode;
//    this.inheritFrom(oLabel, oParent, oExpanded);

    var originalLabel;
    var arguments;
    var predicate;
    
    this.originalLabel = text;
    this.arguments = [];
    this.predicate = null;

    this.updateLabel = function(_arg) {
        this.label = this.originalLabel;

        if (_arg == "")
            return;
            
        var arg = _arg;
        
        if (arg[0] == '$') {
            this.predicate = arg.substr(1);
            arg = 'p' + this.predicate;
        }

        this.arguments.push(arg);

        var size = this.arguments.length;
        if (size < 1)
            return;

        this.label += "(" + this.arguments[0];
        for (var i = 1; i < size; i++)
            this.label += "," + this.arguments[i];
        this.label = this.label + ")";
    }
    
    this.label = text;
}

function Queue(name) {
    this.inheritFrom = Stack;
    this.inheritFrom(name);

    // move the top of stack to front
    this.move = function(stack) {
        var tv = stack.top();
        var nextElement = stack.pop();
        var ni = document.getElementById(this.id);
        ni.insertBefore(nextElement, ni.firstChild);
        this.push(tv);
    }

    this.pushElement = function(element, DOM_element) {
        var ni = document.getElementById(this.id);
        var clonedElement = DOM_element.cloneNode(true);
        ni.insertBefore(clonedElement, ni.firstChild);
        this.push(element);
    }
    
    this.push = function(treeView) {
        this.stack.unshift(treeView);
    }

    this.top = function() {
        if (this.size())
            return this.stack[0];
        else
            return null;
    }

    this.topElement = function() {
        var d = document.getElementById(this.id);
        var child = d.firstChild;
        return child;
    }
    
    // pop both the queue and the DOM, return the popped Element
    this.pop = function() {
        var d = document.getElementById(this.id);
        var child = d.firstChild;
        d.removeChild(child);
        this.stack.shift();
        return child;
    }

    this.addToken = function(label, id) {
        // create the element
        var element = document.createElement('td');
        element.setAttribute('class', 'stack');
        element.setAttribute('className', 'stack'); // IE bug
        var ni = document.getElementById(this.id);
        ni.appendChild(element);

        // create the TreeView
        var tv = new YAHOO.widget.TreeView(element); // shares property id with element
        // add the token
        //var token = new YAHOO.widget.TextNode(label, tv.getRoot(), true);
        var labeledText = new LabeledText(label);
        var token = new YAHOO.widget.TextNode(labeledText, tv.getRoot(), true);
        token.id = id;
        token.labelStyle = 'textNode';

        this.stack.push(tv);
        tv.draw();
    }
}

// create the basic stacks structure
var depStack    = new Stack("depStack");
var srlStack    = new Stack("srlStack");
var inputQueue  = new Queue("inputQueue");

function record(param) {
    var hist = document.getElementById('actions');
    hist.value += param + ' ';
    stepNo++;
}

//
// control functions
//

// link child to head with dep label.
function link(child, head, dep) {
    if (dep) {
        //inputQueue.updateTop(dep, child.id);
        //depStack.updateTop(dep, child.id);
        child.data.updateLabel(dep);
        child.label = child.data.label;
    }
    //if (child.parent != head)
    child.appendTo(head);
    head.parent.refresh();
}

function srlLink(child, head, dep) {
    // versione precedente
    //dep = "p" + head.data.predicate + "." + dep;
    
    // versione che prende il nome originario del predicato
    if (head.data.predicate != null)
    {
		dep = head.data.originalLabel + "." + dep;

		inputQueue.updateAll(dep, child.id);
		depStack.updateAll(dep, child.id);
		head.parent.refresh();
		
		return true;
	}
	/*else if (child.data.predicate != null)
	{
		dep = child.data.originalLabel + "." + dep;

		inputQueue.updateAll(dep, head.id);
		depStack.updateAll(dep, head.id);
		child.parent.refresh();

		return true;
	}*/
        
    //child.data.updateLabel(dep);
    //child.label = child.data.label;
    
    return false;
}

function appendPredicate(node, pred) {
    if (pred != "") {
        var predString = "$" + pred;
        inputQueue.updateTop(predString, node.id);
        depStack.updateTop(predString, node.id);
    }
}

function shift(pred) {
    if (inputQueue.size() < 1)
        return false;
    if (pred == null) {
        var f = document.getElementById('predlabel');
        pred = f.options[f.selectedIndex].value;
        steps.splice(stepNo, steps.length - stepNo, 'S' + pred);
    }
    record('S' + pred);
    depStack.move(inputQueue);
    appendPredicate(inputQueue.topToken(1), pred);
    return true;
}

function left(dep) { return Left(1, dep); }
function left2(dep) { return Left(2, dep); }
function left3(dep) { return Left(3, dep); }

function Left(n, dep) {
    if (depStack.size() < n || inputQueue.size() < 1)
        return false;
    if (n == 1)
        action = 'L';
    else
        action = 'l' + n;
    if (dep == null) {
        var f = document.getElementById('synlabel');
        dep = f.options[f.selectedIndex].value;
        steps.splice(stepNo, steps.length - stepNo, action + dep);
    }
    record(action + dep);

    srlStack.pushToken(inputQueue.topToken(1));
    //srlStack.pushElement(inputQueue.top(), inputQueue.topElement());
    
    link(inputQueue.topToken(), depStack.topToken(n), dep);
    inputQueue.pop();
    for (i = 0; i < n; i++)
        inputQueue.move(depStack);
    return true;
}

function right(dep) { return Right(1, dep); }
function right2(dep) { return Right(2, dep); }
function right3(dep) { return Right(3, dep); }

function Right(n, dep) {
    if (depStack.size() < n || inputQueue.size() < 1)
        return false;
    if (n == 1)
        action = 'R';
    else
        action = 'r' + n;
    if (dep == null) {
        var f = document.getElementById('synlabel');
        dep = f.options[f.selectedIndex].value;
        steps.splice(stepNo, steps.length - stepNo, action + dep);
    }
    record(action + dep);

    srlStack.pushToken(depStack.topToken(n))
    //srlStack.pushElement(depStack.top(), depStack.topElement());
    
    link(depStack.topToken(n), inputQueue.topToken(), dep);
    depStack.remove(n);
    if (n > 1)
        inputQueue.move(depStack); // anomaly
    return true;
}


function srl_left(dep) {
    // old version
    //if (srlStack.size() < 1 || depStack.size() < 1)
    // new version
    if (srlStack.size() < 1 || inputQueue.size() < 1)
        return false;
    action = '_l';
    if (dep == null) {
        var f = document.getElementById('srllabel');
        dep = f.options[f.selectedIndex].value;
        steps.splice(stepNo, steps.length - stepNo, action + dep);
    }
    // old version
    //if (srlLink(srlStack.topToken(1), depStack.topToken(1), dep))
    // new version
    if (srlLink(inputQueue.topToken(), srlStack.topToken(1), dep))
    {
		record(action + dep);
		return true;
    }
    return false;
}

function srl_right(dep) {
    if (srlStack.size() < 1 || inputQueue.size() < 1)
        return false;
    action = '_r';
    if (dep == null) {
        var f = document.getElementById('srllabel');
        dep = f.options[f.selectedIndex].value;
        steps.splice(stepNo, steps.length - stepNo, action + dep);
    }
    if (srlLink(srlStack.topToken(1), inputQueue.topToken(), dep))
    {
    	record(action + dep);
		return true;
    }
    return false;
}

function srl_pop(arg) {
    if (srlStack.size() < 1)
        return false;
    action = '_p';
    if (!arg)
        steps.splice(stepNo, steps.length - stepNo, action);
    record(action);
    srlStack.remove(1);
    return true;
}




// Reads sentence and initialize the system
function init(rewind) {
    // clear stacks
    depStack.clear();
    srlStack.clear();
    inputQueue.clear();
    if (!rewind)
        steps = [];
    stepNo = 0;
    var f = document.getElementById('actions');
    f.value = '';

    var sen = document.getElementById('sentence');
    var words = sen.value.split(' ');
    for (var i = 0; i < words.length; ++i)
        inputQueue.addToken(words[i], i);
}

function setLanguage() {
    var f = document.getElementById('languageChoice');
    var synLabels = synLabelsAll[f.selectedIndex];
    f = document.getElementById('synlabel');
    var l = f.length;
    for (var i = 0; i < l; i++)
        f.remove(0);
    for (var i in synLabels) {
        var opt = document.createElement('option');
        opt.text = synLabels[i];
        f.add(opt, null);
    }
    f = document.getElementById('srllabel');
    var l = f.length;
    for (var i = 0; i < l; i++)
        f.remove(0);
    for (var i in srlLabels) {
        var opt = document.createElement('option');
        opt.text = srlLabels[i];
        f.add(opt, null);
    }
}

var steps = [];
var stepNo = 0;

// return whether action succeeded
function step(action) {
    var param = action.substr(1);
    switch (action[0]) {
        case 'S':
            return shift(param);
        case 'L':
            return Left(1, param);
        case 'R':
            return Right(1, param);
        case 'l':
            return Left(param[0], param.substr(1));
        case 'r':
            return Right(param[0], param.substr(1));
        case '_':
        {
            if (param[0] == 'l')
                return srl_left(param.substr(1));
            else
            if (param[0] == 'r')
                return srl_right(param.substr(1));
            else
            if (param[0] == 'p')
                return srl_pop(true);
        }       
    }
    return false; // action failed
}

// Perform the steps in the Action list
function actions(dir) {
    var hist = document.getElementById('actions');
    switch (dir) {
        case -2:
            init(true);
            break;
        case -1:
            var s = stepNo;
            init(true);
            for (var i = 0; i < s - 1; i++)
                step(steps[i]);
            break;
        case 1:
            if (stepNo < steps.length)
                step(steps[stepNo]);
            break;
        case 2:
            while (stepNo < steps.length)
                if (!step(steps[stepNo]))
                break;
            break;
    }
}

function setActions() {
    var acts = document.getElementById('actions');
    steps = acts.value.split(' ');
    actions(-2);
}

// Syntactic Actions
var synAction = ["shift", "left", "right", "left2", "right2", "left3", "right3"];

var synLabelsAll = [
   ["_", "SBJ", "OBJ", "IOBJ", "ADV", "COORD", "CONJ", "GAP", "P", "AMOD", "NMOD", "PMOD", "VC", "VMOD"],
   ["_", "arg", "aux", "clit", "comp", "comp_ind", "comp_loc", "comp_temp",
    "con", "concat", "conj", "det", "dis", "disj", "mod", "modal", "mod_loc",
    "mod_rel", "mod_temp", "neg", "obj", "pred", "pred_loc", "prep", "punc",
    "ROOT", "sub", "subj", "subj_pass"]
];

// SRL Actions
var srlAction = ["srl_left", "srl_right", "srl_pop"];

var predLabels = ["", "0", "1", "2", "3"];
var srlLabels = ["A0", "A1", "A2", "A3", "A4"];

var languages = ["English", "Italian"];