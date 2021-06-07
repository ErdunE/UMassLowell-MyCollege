/*
Full Name: Erdun E
E-mail: Erdun_E@student.uml.edu
Affiliation: Umass Lowell 91.61 GUI Programming 1
Date: 2020-08-08
Web Address: https://erdune.github.io/GUI-Programming-1-HW7/
Description: This assignment is building on HW6 that using the jQuery validation plugin with my dynamic table then using the jQuery UI slider and tab widgets to make this page more complete!
Reference: https://www.w3schools.com/
*/


function TableStart() {
    clearInvalid();
    clearTable();
    var isAllDone = false;
    /* get data of multiplier and multiplicand from user input */
    var row1 = $('#row1').val();
    var row2 = $('#row2').val();
    var col1 = $('#col1').val();
    var col2 = $('#col2').val();

    // if (!row1 || !row2 || !col1 || !col2) {
    //     alert('plz enter all number');
    //     return ;
    // }
    /* output read value to console */
    console.log(row1);
    console.log(row2);
    console.log(col1);
    console.log(col2);

    /*if (!row1 || Number(row1) < -50) {
        addInvalid('row1Text', 'Invalid input, plase enter a number not less than -50.')
        isAllDone = true;
    }
    if (!row2 || Number(row2) > 50) {
        addInvalid('row2Text', 'Invalid input, plase enter a number not bigger than 50.')
        isAllDone = true;
    }
    if (!col1 || Number(col1) < -50) {
        addInvalid('col1Text', 'Invalid input, plase enter a number not less than -50.')
        isAllDone = true;
    }
    if (!col2 || Number(col2) > 50) {
        addInvalid('col2Text', 'Invalid input, plase enter a number not bigger than 50.')
        isAllDone = true;
    }

    /* check if start number greater than end
       check number is negative */
    /*if ((Number(row1) > Number(row2)) && (Number(row1) >= 0)) {
        addInvalid('row2Text', 'Invalid input for multiplier. The ending number must bigger than starting number.')
        isAllDone = true;
    }

    /* check if start number greater than end
       check number is negative */
    /*if ((Number(col1) > Number(col2)) && (Number(col1) >= 0)) {
        addInvalid('col2Text', 'Invalid input for multiplier. The ending number must bigger than starting number.')
        isAllDone = true;
    }*/

    /* get row and colnum length */
    var rowlength = row2 - row1 + 1;
    var collength = col2 - col1 + 1;

    /* check if table to long */
    /*if (rowlength > 101) {
        addInvalid('row2Text', 'Invalid Range. The range of row cannot large than 100.')
        isAllDone = true;
    }

    /* check if table to height */
    /*if (collength > 101) {
        addInvalid('col2Text', 'Invalid Range. The range of row cannot large than 100.')
        isAllDone = true;
    }
    if (isAllDone) return;
    /* initial table html and count number i, j */
    var TableFormat = "<table>";
    var i, j;

    /* add table header line to html */
    TableFormat += "<tr><th></th>";
    for (i = 0; i < rowlength; i++) {
        TableFormat += "<th>";
        var num = Number(row1) + i;
        TableFormat += num;
        TableFormat += "</th>";
    }
    TableFormat += "</tr>";

    /* add table data to html */
    for (i = 0; i < collength; i++) {
        TableFormat += "<tr>";
        var colnum = Number(col1) + i;
        for (j = 0; j < rowlength + 1; j++) {
            TableFormat += "<td>";
            if (j == 0) {
                TableFormat += colnum;
            } else {
                var rownum = Number(row1) + j - 1;
                var num = colnum * rownum;
                TableFormat += num;
            }
            TableFormat += "</td>";
        }
        TableFormat += "</tr>";
    }
    TableFormat += "</table>";

    /* output whole table to screen */
    document.getElementById('table').innerHTML = TableFormat;
}

function addInvalid(className, text) {
    var el = document.getElementsByClassName(className);
    console.log(el, text)
    el[0] && (el[0].innerText = text);
}

function clearInvalid() {
    addInvalid('row1Text', '');
    addInvalid('row2Text', '');
    addInvalid('col1Text', '');
    addInvalid('col2Text', '');
}

function clearTable() {
    document.getElementById('table').innerHTML = '';
}
