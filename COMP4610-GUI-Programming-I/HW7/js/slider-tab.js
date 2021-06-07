/*
Full Name: Erdun E
E-mail: Erdun_E@student.uml.edu
Affiliation: Umass Lowell 91.61 GUI Programming 1
Date: 2020-08-08
Web Address: https://erdune.github.io/GUI-Programming-1-HW7/
Description: This assignment is building on HW6 that using the jQuery validation plugin with my dynamic table then using the jQuery UI slider and tab widgets to make this page more complete!
Reference: https://www.w3schools.com/
           https://jqueryvalidation.org/
           https://stackoverflow.com/questions/32587177/jquery-validate-compare-two-fields
*/

$(function()
{

    // create the star table
    CreateTable();
    // create the slider
    SliderInput();

    $(".button").click(function() {
        // create the subtab
        CreateTab();
        // create the Delete All button
        var del = '<button type="button">Delete All Tab</button>';
        document.getElementById("rm").innerHTML = del;
    });

    $("#tabs").on("click", "span.ui-icon-close", function() {
        // remove current tab
        var panelId = $(this).closest("li").remove().attr("aria-controls");
        $("#" + panelId).remove();
        $("#tabs").tabs("refresh");
        // remove tab list and delete all button
        if($("#tabs ul li").length == 0) {
            $(".ui-tabs").tabs("destroy");
            document.getElementById("rm").innerHTML = "";
        }
    });

    // delete all tab
    $("#rm").click(function() {
        document.getElementById("tabs").innerHTML = "<ul></ul>";
        $(".ui-tabs").tabs("destroy");
        document.getElementById("rm").innerHTML = "";
    });
});

// slider function
function SliderInput() {
    // create the slider for range (-50, 50)
    $("#xBegin").slider({
        min: -50,
        max: 50,
        slide: function(event, ui) {
            $("#row1").val(ui.value);
            CreateTable();
        }
    });
    $("#row1").on("keyup", function() {
        $("#xBegin").slider("value", this.value);
        CreateTable();
    });

    $("#xEnd").slider({
        min: -50,
        max: 50,
        slide: function(event, ui) {
            $("#row2").val(ui.value);
            CreateTable();
        }
    });
    $("#row2").on("keyup", function() {
        $("#xEnd").slider("value", this.value);
        CreateTable();
    });

    $("#yBegin").slider({
        min: -50,
        max: 50,
        slide: function(event, ui) {
            $("#col1").val(ui.value);
            CreateTable();
        }
    });
    $("#col1").on("keyup", function() {
        $("#yBegin").slider("value", this.value);
        CreateTable();
    });

    $("#yEnd").slider({
        min: -50,
        max: 50,
        slide: function(event, ui) {
            $("#col2").val(ui.value);
            CreateTable();
        }
    });
    $("#col2").on("keyup", function() {
        $("#yEnd").slider("value", this.value);
        CreateTable();
    });
}

// create the  tab
function CreateTab()
{
    // tab number
    var num = $("#tabs ul li").length + 1;
    if(num > 20)
    {
        alert("Cannot create more than 20 tabs.");
        return false;
    }


    if($("#row1").valid() && $("#row2").valid() && $("#col1").valid() && $("#col2").valid())
    {
        $("#tabs").tabs();
        $("#tabs ul").append("<li><a href='#tab-" + num + "'>Tab " + num + "</a><span class='ui-icon ui-icon-close' role='presentation'></span></li>");
        $("#tabs").append("<div id='tab-" + num + "'>" + $("#table").html() + "</div>");
        $("#tabs").tabs("refresh");
        $("#tabs").tabs("option", "active", -1);
    }
    else
    {
        alert("Please check your input values!");
        return false;
    }
}
