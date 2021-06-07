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

function valid_in()
{
    /* set the end number to be greater than the start number  */
    $.validator.addMethod("larger", function(value, element, param)
    {
        return this.optional(element) || parseInt(value) >= parseInt($(param).val());
    }, 'Invalid value');

    /* set the range of start to end is less than 100 */
    $.validator.addMethod("length", function(value, element, param)
    {
        return this.optional(element) || Math.abs(parseInt(value) - parseInt($(param).val())) < parseInt(101);
    }, 'Invalid value');

    /* The validation will check stuff is following:
       1. check it is a field empty
       2. check it is a number
       3. check the input in range -100 to 100
       4. check it is the End larger or equal start
       5. check it is length from start to end larger 100 */

    $("#subForm").validate
    ({
        rules:
        {
            row1:
            {
                required: true,
                number: true,
                min: -50,
                max: 50
            },
            row2:
            {
                required: true,
                number: true,
                min: -50,
                max: 50,
                larger: "#row1",
                length: "#row1"
            },
            col1:
            {
                required: true,
                number: true,
                min: -50,
                max: 50
            },
            col2:
            {
                required: true,
                number: true,
                min: -50,
                max: 50,
                larger: "#col1",
                length: "#col1"
            }
        },
        messages:
        {
            row1:
            {
                required: "The field cannot empty!",
                number: "Please enter a normal number!",
                min: "The number cannot less than -50!",
                max: "The number cannot greater than 50!"
            },
            row2:
            {
                required: "The field cannot empty!",
                number: "Please enter a normal number!",
                min: "The number cannot less than -50!",
                max: "The number cannot greater than 50!",
                larger: "End number must larger or equal to start number!",
                length: "The range from start to end cannot greater than 100!"
            },
            col1:
            {
                required: "The field cannot empty!",
                number: "Please enter a normal number!",
                min: "The number cannot less than -50!",
                max: "The number cannot greater than 50!"
            },
            col2:
            {
                required: "The field cannot empty!",
                number: "Please enter a normal number!",
                min: "The number cannot less than -50!",
                max: "The number cannot greater than 50!",
                larger: "End number must larger or equal to start number!",
                length: "The range from start to end cannot greater than 100!"
            }
        }
    });
}

function CreateTable()
{

    valid_in();

    if($("#row1").valid() && $("#row2").valid() && $("#col1").valid() && $("#col2").valid())
    {
        TableStart();
    };
}
