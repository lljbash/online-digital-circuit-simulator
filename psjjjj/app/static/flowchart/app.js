var app = angular.module('app', ['flowchart']);
  app.factory('prompt', function () {
    return prompt;
  });
  app.config(function (NodeTemplatePathProvider) {
    NodeTemplatePathProvider.setTemplatePath("flowchart/node.html");
  });

  app.controller('AppCtrl', function AppCtrl($scope, $http, $location, prompt, Modelfactory, flowchartConstants) {

    var deleteKeyCode = 46;
    var ctrlKeyCode = 17;
    var aKeyCode = 65;
    var escKeyCode = 27;
    var nextNodeID = 10;
    var nextConnectorID = 20;
    var ctrlDown = false;
    $scope.filename = "example.txt"

    var model = {
      nodes: [
        {
          name: "Activation",
          id: 2,
          x: 400,
          y: 100,
          color: '#000',
          borderColor: '#000',
          connectors: [
            {
              type: flowchartConstants.bottomConnectorType,
              id: 9
            },
            {
              type: flowchartConstants.bottomConnectorType,
              id: 10
            }
          ]
        },
        {
          name: "Chip1",
          id: 3,
          x: 400,
          y: 300,
          color: '#F15B26',
          connectors: [
            {
              type: flowchartConstants.topConnectorType,
              id: 1
            },
            {
              type: flowchartConstants.topConnectorType,
              id: 3
            },
            {
              type: flowchartConstants.bottomConnectorType,
              id: 4
            },
            {
              type: flowchartConstants.bottomConnectorType,
              id: 5
            }
          ]
        },
        {
          name: "Chip2",
          id: 4,
          x: 250,
          y: 500,
          color: '#000',
          borderColor: '#000',
          connectors: [
            {
              type: flowchartConstants.topConnectorType,
              id: 13
            },
            {
              type: flowchartConstants.topConnectorType,
              id: 14
            },
            {
              type: flowchartConstants.topConnectorType,
              id: 15
            }
          ]
        },
        {
          name: "Chip3",
          id: 5,
          x: 550,
          y: 500,
          color: '#000',
          borderColor: '#000',
          connectors: [
            {
              type: flowchartConstants.topConnectorType,
              id: 16
            },
            {
              type: flowchartConstants.topConnectorType,
              id: 17
            },
            {
              type: flowchartConstants.topConnectorType,
              id: 18
            }
          ]
        }
      ],
    edges: [
      {
        source: 10,
        destination: 1
      },
      {
        source: 4,
        destination: 14
      },
      {
        source: 5,
        destination: 17
      }
    ]
  };

$scope.flowchartselected = [];
var modelservice = Modelfactory(model, $scope.flowchartselected);

$scope.model = model;
$scope.inputArray = new Array();
$scope.inputNum = 0;
$scope.modelservice = modelservice;

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

$scope.addNewNode = function () {
  var nodeName = prompt("Chip type:", "New node");
  $http({
    method:'POST',
    data:{'data' : nodeName},
    url:'/add'
  }).then(function successCallback(response){
    if (!nodeName) {
      return;
    }
    console.log(response.data);
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
    var newNode = {
      name: nodeName,
      id: nextNodeID++,
      x: 200,
      y: 100,
      color: '#F15B26',
      connectors: connectors_array
    };
    model.nodes.push(newNode);
  }, function errorCallback(response){
  });
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
    console.log(response.data);
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
    var newNode = {
      name: data,
      id: nextNodeID++,
      x: 200,
      y: 100,
      color: '#F15B26',
      connectors: connectors_array
    };
    model.nodes.push(newNode);
  }, function errorCallback(response){
  });
});

$scope.activateWorkflow = function() {

  $http({
    method: 'POST',
    data: {'data' : model, 'activation':$scope.inputArray},
    url: '/test'
  }).then(function successCallback(response) {

    console.log(response.data);
    $scope.filename = response.data;
    if(response.data == "error"){
        console.log("error");
        window.location = '/error';
    }
    else{
        console.log("success");
        var redirect_url = "/submitted/" + $scope.filename;
        window.location = redirect_url;
    }
  }, function errorCallback(response) {

  });
// Original Code
//  angular.forEach($scope.model.edges, function(edge) {
//    edge.active = !edge.active;
//  });
};

$scope.inputActivation = function() {
    var selectedNodes = modelservice.nodes.getSelectedNodes();
    angular.forEach(selectedNodes, function(node){
        var inputType_s = prompt("Please input your activation(0/1):", '0');
        var inputType = parseInt(inputType_s);
        $scope.inputArray[$scope.inputNum++] = {input:inputType, id:node.id};
        console.log('inputType:' + inputType);
    });
};

$scope.addNewInputConnector = function () {
  var connectorName = prompt("Enter a connector name:", "New connector");
  if (!connectorName) {
    return;
  }

  var selectedNodes = modelservice.nodes.getSelectedNodes($scope.model);
  for (var i = 0; i < selectedNodes.length; ++i) {
    var node = selectedNodes[i];
    node.connectors.push({id: nextConnectorID++, type: flowchartConstants.topConnectorType});
  }
};

$scope.addNewOutputConnector = function () {
  var connectorName = prompt("Enter a connector name:", "New connector");
  if (!connectorName) {
    return;
  }

  var selectedNodes = modelservice.nodes.getSelectedNodes($scope.model);
  for (var i = 0; i < selectedNodes.length; ++i) {
    var node = selectedNodes[i];
    node.connectors.push({id: nextConnectorID++, type: flowchartConstants.bottomConnectorType});
  }
};

$scope.deleteSelected = function () {
  modelservice.deleteSelected();
};

$scope.callbacks = {
  edgeDoubleClick: function () {
    console.log('Edge double clicked.');
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
});