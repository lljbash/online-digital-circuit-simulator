var app = angular.module('app', ['flowchart']);
  app.factory('prompt', function () {
    return prompt;
  });
  app.config(function (NodeTemplatePathProvider) {
    NodeTemplatePathProvider.setTemplatePath("flowchart/node.html");
  });

  app.controller('AppCtrl', function AppCtrl($scope, $http, $location, prompt, Modelfactory, flowchartConstants) {

    var offsetNum = 0;
    var deleteKeyCode = 46;
    var ctrlKeyCode = 17;
    var aKeyCode = 65;
    var escKeyCode = 27;
    var nextNodeID = 10;
    var nextConnectorID = 20;
    var ctrlDown = false;
    $scope.filename = "example.txt";
    var model = {nodes:[], edges:[]};
    var url = $location.absUrl();
    var items = url.split("/");
    var length = items.length;
    var itemID = items[length-1];
    var submissionID = '';
    var tested = false;
    if (length == 7) { 
        itemID = items[length -2];
        submissionID = items[length - 1];
    }
    console.log(length)
    console.log(url);
    $http({
      method:'POST',
      data:{'itemID' : itemID, 'submissionID' : submissionID},
      url:'/load'
    }).then(function successCallback(response){
      console.log("success!");
      console.log(response.data);
      var nodes = response.data.nodes;
      var edges = response.data.edges;
      console.log(nodes);
      console.log(edges);
      var length = nodes.length;
    
      for(var i=0;i<length;i++){
        model.nodes.push(nodes[i]);
	nextNodeID = Math.max(nextNodeID, nodes[i].id) + 1;
	var connectorLength = nodes[i].connectors.length;
	for(var j=0;j<connectorLength;j++){
	  var connector = nodes[i].connectors[j];
	  nextConnectorID = Math.max(nextConnectorID, connector.id) + 1;
        }
      }
      length = edges.length;
      for(var i=0;i<length;i++){
        model.edges.push(edges[i]);
      }
    


    }, function errorCallback(response){
      console.log("error!");  
    });
$scope.flowchartselected = [];
var modelservice = Modelfactory(model, $scope.flowchartselected);

$scope.model = model;
$scope.inputArray = new Array();
$scope.inputNum = 0;
$scope.modelservice = modelservice;
$scope.tested = tested;

$scope.keyDown = function (evt) {
  if (evt.keyCode === ctrlKeyCode) {
    ctrlDown = true;
    evt.stopPropagation();
    evt.preventDefault();
  }
};

$scope.keyUp = function (evt) {

  if (evt.keyCode === deleteKeyCode) {
    modelservice.deleteSelected();
  }

  if (evt.keyCode == aKeyCode && ctrlDown) {
    modelservice.selectAll();
  }

  if (evt.keyCode == escKeyCode) {
    modelservice.deselectAll();
  }

  if (evt.keyCode === ctrlKeyCode) {
    ctrlDown = false;
    evt.stopPropagation();
    evt.preventDefault();
  }
};

$scope.$on('addnode', function(event, data){
  $http({
    method:'POST',
    data:{'data' : data},
    url:'/add'
  }).then(function successCallback(response){
    if (!data) {
      return;
    }
    var nodeName = prompt("Chip name:", "New node");
    var pinsNum = parseInt(response.data);
    var connectors_array = new Array();
    for(var i=0;i<pinsNum;i++){
        if(i<pinsNum / 2){
            connectors_array[i] = { id:nextConnectorID++,type:flowchartConstants.topConnectorType};
        }
        else{
            connectors_array[i] = { id:nextConnectorID++,type:flowchartConstants.bottomConnectorType};
        }
    }
    var _x = 50 + (offsetNum % 5) * 20;
    var _y = 60 + (offsetNum % 5 + offsetNum / 5) * 10;
    var newNode = {
      name: nodeName + "(" + data + ")",
      ano_name : nodeName,
      type: data,
      id: nextNodeID++,
      x: _x,
      y: _y,
      color: '#F15B26',
      connectors: connectors_array
    };
    model.nodes.push(newNode);
    offsetNum++;
  }, function errorCallback(response){
  });
});

$scope.submit_circuit = function(itemID) {

  $http({
    method: 'POST',
     data: {'data' : model, 'itemID':itemID},
    url: '/simulate'
  }).then(function successCallback(response) {

    console.log(response.data);
    $scope.filename = response.data;
    if(response.data === "error"){
        console.log("error");
        window.location = '/error';
    }
  }, function errorCallback(response) {

  });
};

$scope.showVHDL = function(submissionID) {
  window.open('/showvhdl/' + submissionID, 'newwindow');
}

$scope.test_circuit = function(itemID) {

  $http({
    method: 'POST',
     data: {'data' : model, 'itemID':itemID},
    url: '/test'
  }).then(function successCallback(response) {

    console.log(response.data);
    if(response.data === "error"){
        console.log("error");
        window.location = '/error';
    }
    else{
        $scope.filename = response.data;
        $scope.tested = true;
    }
  }, function errorCallback(response) {

  });
};

$scope.save_circuit = function(itemID) {
  console.log(itemID);
  $http({
    method: 'POST',
     data: {'data' : model, 'itemID':itemID},
    url: '/save'
  }).then(function successCallback(response) {
	console.log(itemID);
   
  }, function errorCallback(response) {

  });
}

$scope.downloadResult = function() {
  var redirect_url = "/download/" + $scope.filename;
  window.open(redirect_url, 'newwindow');
};

$scope.showResult = function() {
  window.location = "/result/" + $scope.filename + ".png";
};

$scope.deleteSelected = function () {
  modelservice.deleteSelected();
};

$scope.callbacks = {
  edgeDoubleClick: function () {
    console.log('Edge double clicked.');
    $scope.deleteSelected();
  },
  edgeMouseOver: function () {
    console.log('mouserover')
  },
  isValidEdge: function (source, destination) {
    return true;
  },
  edgeAdded: function (edge) {
    console.log("edge added");
    console.log(edge);
  },
  nodeRemoved: function (node) {
    console.log("node removed");
    console.log(node);
  },
  edgeRemoved: function (edge) {
    console.log("edge removed");
    console.log(edge);
  },
  nodeCallbacks: {
    'doubleClick': function (event) {
      console.log('Node was doubleclicked.')
      $scope.deleteSelected();
    }
  }
};
modelservice.registerCallbacks($scope.callbacks.edgeAdded, $scope.callbacks.nodeRemoved, $scope.callbacks.edgeRemoved);

})
;

app.controller('AppCtrl2', function AppCtrl($scope, $http){
  $scope.add_mod_74ls00 = function(){
    $scope.$emit('addnode', "MOD_74LS00");
  };
  $scope.add_mod_74ls04 = function(){
    $scope.$emit('addnode', "MOD_74LS04");
  };
  $scope.add_mod_74ls11 = function(){
    $scope.$emit('addnode', "MOD_74LS11");
  };
  $scope.add_mod_74ls20 = function(){
    $scope.$emit('addnode', "MOD_74LS20");
  };
  $scope.add_mod_64ls27 = function() {
    $scope.$emit('addnode', "MOD_74LS27");
  };
  $scope.add_mod_74ls86 = function() {
    $scope.$emit('addnode', "MOD_74LS86");
  };
  $scope.add_nand_gate4 = function() {
    $scope.$emit('addnode', "NAND_GATE4");
  };
  $scope.add_nand_gate2 = function() {
    $scope.$emit('addnode', "NAND_GATE2");
  };
  $scope.add_and_gate3 = function() {
    $scope.$emit('addnode', "AND_GATE3");
  };
  $scope.add_nor_gate3 = function() {
    $scope.$emit('addnode', "NOR_GATE3");
  };
  $scope.add_xnor_gate2 = function() {
    $scope.$emit('addnode', "XNOR_GATE2");
  };
  $scope.add_input = function() {
    $scope.$emit('addnode', "input");
  };
  $scope.add_output = function() {
    $scope.$emit('addnode', "output");
  };
  $scope.add_vcc = function() {
    $scope.$emit('addnode', "vcc");
  }
  $scope.add_gnd = function() {
    $scope.$emit('addnode', "gnd")
  }
});
