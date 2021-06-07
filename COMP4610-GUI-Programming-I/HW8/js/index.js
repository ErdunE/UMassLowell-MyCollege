/*
Full Name: Erdun E
E-mail: Erdun_E@student.uml.edu
Affiliation: Umass Lowell 91.61 GUI Programming 1
Date: 2020-08-12
Web Address: https://erdune.github.io/GUI-Programming-1-HW8/
Description: This is the html file to create basic format of scrabble slots,
             word and score place remain, letter tile and rack place remain,
             reset button with click function.
Reference: https://www.w3schools.com/
*/

/**
 * @description: AuthorName
 * @param {type}
 * @return {type}
 */

 /* set tiles value, totlecount, currentcount, and image */
const tileNumList = [
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    '_'
]
var Tiles = [];
Tiles["A"] = {
    "value": 1,
    "totalCount": 9,
    "currCount": 9,
    "image": "public/images/Scrabble_Tile_A.jpg"
};
Tiles["B"] = {
    "value": 3,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_B.jpg"
};
Tiles["C"] = {
    "value": 3,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_C.jpg"
};
Tiles["D"] = {
    "value": 2,
    "totalCount": 4,
    "currCount": 4,
    "image": "public/images/Scrabble_Tile_D.jpg"
};
Tiles["E"] = {
    "value": 1,
    "totalCount": 12,
    "currCount": 12,
    "image": "public/images/Scrabble_Tile_E.jpg"
};
Tiles["F"] = {
    "value": 4,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_F.jpg"
};
Tiles["G"] = {
    "value": 2,
    "totalCount": 3,
    "currCount": 3,
    "image": "public/images/Scrabble_Tile_G.jpg"
};
Tiles["H"] = {
    "value": 4,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_H.jpg"
};
Tiles["I"] = {
    "value": 1,
    "totalCount": 9,
    "currCount": 9,
    "image": "public/images/Scrabble_Tile_I.jpg"
};
Tiles["J"] = {
    "value": 8,
    "totalCount": 1,
    "currCount": 1,
    "image": "public/images/Scrabble_Tile_J.jpg"
};
Tiles["K"] = {
    "value": 5,
    "totalCount": 1,
    "currCount": 1,
    "image": "public/images/Scrabble_Tile_K.jpg"
};
Tiles["L"] = {
    "value": 1,
    "totalCount": 4,
    "currCount": 4,
    "image": "public/images/Scrabble_Tile_L.jpg"
};
Tiles["M"] = {
    "value": 3,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_M.jpg"
};
Tiles["N"] = {
    "value": 1,
    "totalCount": 6,
    "currCount": 6,
    "image": "public/images/Scrabble_Tile_N.jpg"
};
Tiles["O"] = {
    "value": 1,
    "totalCount": 8,
    "currCount": 8,
    "image": "public/images/Scrabble_Tile_O.jpg"
};
Tiles["P"] = {
    "value": 3,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_P.jpg"
};
Tiles["Q"] = {
    "value": 10,
    "totalCount": 1,
    "currCount": 1,
    "image": "public/images/Scrabble_Tile_Q.jpg"
};
Tiles["R"] = {
    "value": 1,
    "totalCount": 6,
    "currCount": 6,
    "image": "public/images/Scrabble_Tile_R.jpg"
};
Tiles["S"] = {
    "value": 1,
    "totalCount": 4,
    "currCount": 4,
    "image": "public/images/Scrabble_Tile_S.jpg"
};
Tiles["T"] = {
    "value": 1,
    "totalCount": 6,
    "currCount": 6,
    "image": "public/images/Scrabble_Tile_T.jpg"
};
Tiles["U"] = {
    "value": 1,
    "totalCount": 4,
    "currCount": 4,
    "image": "public/images/Scrabble_Tile_U.jpg"
};
Tiles["V"] = {
    "value": 4,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_V.jpg"
};
Tiles["W"] = {
    "value": 4,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_W.jpg"
};
Tiles["X"] = {
    "value": 8,
    "totalCount": 1,
    "currCount": 1,
    "image": "public/images/Scrabble_Tile_X.jpg"
};
Tiles["Y"] = {
    "value": 4,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_Y.jpg"
};
Tiles["Z"] = {
    "value": 10,
    "totalCount": 1,
    "currCount": 1,
    "image": "public/images/Scrabble_Tile_Z.jpg"
};
Tiles["_"] = {
    "value": 0,
    "totalCount": 2,
    "currCount": 2,
    "image": "public/images/Scrabble_Tile_Blank.jpg"
};
/* set the number of board and prevboard */
let Board = ['', '', '', '', '', '', '']
let prevBoard = ['', '', '', '', '', '', '']
let positionArr = []
/* set the start value of score and highestscore */
let score = 0
let highestScore = 0
let dict = [] // dictArr
let spareReplaceTIle = ''
let replaceIndex = ''
/* import the dictionary link from this web */
$(window).load(function() {
    initTileBoard();
    $.ajax({
        url: "https://erdune.github.io/GUI-Programming-1-HW8/public/dictionary.txt",
        success: function(result) {
            var words = result.split("\n");
            for (var i = 0; i < words.length; ++i) {
                dict.push([words[i].toUpperCase()]);
            }
        }
    });
    /* droppabe function */
    $(".square").droppable({
        accept: ".dragItem",
        activeClass: "dragHighlight",
        hoverClass: "hoverHighlight",
        drop: function(event, ui) {
            let str = event.target.id
            let index = str[str.length - 1] - 1
            if (isBoardValidate(index)) {
                let newTile, letter
                $(event.toElement).css('display', 'none')
                if (ui.draggable.attr("letter") == '_') {
                    replaceIndex = index
                    initSpace()
                    letter = ui.draggable.attr("letter")
                    newTile = $(`<img src=${Tiles[letter]["image"]} class="dragItem" letter=${letter} id="spareBoard"/>`);
                } else {
                    letter = ui.draggable.attr("letter")
                    newTile = $(`<img src=${Tiles[letter]["image"]} class="dragItem" letter=${letter} />`);
                }
                $(this).append(newTile)
                Board[index] = letter
                culculateScore(Board)
            } else {
                ui.offset = positionArr[index]
                ui.position = positionArr[index]
            }
        }
    });
});
/* set the board validate */
function isBoardValidate(index) {
    // 1. null
    if (!Board.join().replace(/,/g, "")) {
        return true
    }
    if (index == 0 && Board[1] !== '') {
        return true
    }
    if (Board[index - 1] || Board[index + 1]) {
        return true
    }
    if (Board[index]) {
        alert('There are letters in this position, please reposition!')
        return false
    }
    alert('Please confirm that there are gaps between letters!')
    return false
}


/**
 * @description:
 * @param {type}
 * @return {type}
 */
 /* set the score culcalation functon */
function culculateScore(Board) {
    let word = Board.join().replace(/,/g, "")

    $('#word').html(`<span>${word}</span>`)
    if (word.length >= 2) {
        let i = 0
        $('#oneWordCheckIcon').removeClass('instructionIcon')
        $('#minLengthIcon').removeClass('instructionIcon')
        for (i = 0; i < dict.length; i++) {
            if (dict[i][0].indexOf(word) > -1) {
                $('#dictionaryCheckIcon').removeClass('instructionIcon')
                if ($('.instructionIcon').length == 0) {
                    $("#nextWordButton").attr('disabled', false);
                }
                break
            }
        }
        if (i == dict.length) {
            $('#dictionaryCheckIcon').addClass('instructionIcon')
            $("#nextWordButton").attr('disabled', true);
        }
    } else {
        $('#oneWordCheckIcon').addClass('instructionIcon')
        $('#minLengthIcon').addClass('instructionIcon')
    }
    for (let i = 0; i < Board.length; i++) {
        if (Board[i] != prevBoard[i]) {
            if (i == 1 || i == 5) {
                score += (Tiles[Board[i]].value) * 2
            } else {
                score += Tiles[Board[i]].value
            }
        }
    }
    prevBoard = JSON.parse(JSON.stringify(Board))
        // console.log('score', score)
    $('#score').html(`<span>${score}</span>`)
}

/**
 * @description: init tileRack Board => append img to #tileRack
 *               recycle current hand and reInitTileRacks
 * @param {type}
 * @return {type}
 */
function initTileBoard(isReset) {
    if (isReset) {
        initTiles()
    }
    while ($('.tileRack img').length < 7 || calculateRemain() < 7) {
        let index = Random(0, 26)
        let currentLetter = tileNumList[index]
            // console.log('currentLetter', currentLetter, index)
        if (Tiles[currentLetter].currCount > 0) {
            let newTile = $(`<img id=${$('.tileRack').length-1} src=${Tiles[currentLetter]["image"]} class="dragItem" letter=${currentLetter} />`);
            $('.tileRack').append(newTile)
            newTile.draggable({
                revertDuration: 200, // msec
                start: function(event, ui) {
                    // Tile should be on top of everything else when being dragged.
                    $(this).css("z-index", 100);
                    // Revert option needs to be manually reset because it may be modified by droppables
                    // to force reverting after dropping has occured.
                    $(this).draggable("option", "revert", "invalid");
                    // $('.square').addClass('dragHighlight')
                },
                // stop: function(event, ui) {
                //     // Once finished dragging, revert the z-index.
                //     console.log('stop dtagger')
                //     let str = event.target.id
                //     let index = str[str.length - 1] - 1
                //     isBoardValidate(index)
                //     $(this).css("z-index", "1");
                //     // $('.square').removeClass('dragHighlight')
                // }
            }).each(function() {
                var top = $(this).position().top;
                var left = $(this).position().left;
                $(this).data('orgTop', top);
                $(this).data('orgLeft', left);
                positionArr.push({
                        "orgTop": top,
                        "orgLeft": left
                    })
                    // console.log('$(this).data', top, left)
            });
            Tiles[currentLetter].currCount--
        }
        let remainSum = calculateRemain()
        $('#remain').html(`<span>${remainSum}</span>`)
    }
}

function calculateRemain() {
    let sum = 0
    Object.values(Tiles).map(item => {
        sum += item.currCount
    })
    return sum
}

/**
 * @description:
 * @param {type}
 * @return {type}
 */
function generateTileId() {
    var id;
    generateTileId.id = ++generateTileId.id || 1;
    id = "tile" + generateTileId.id.toString();
    return id;
}

/**
 * @description: recycleHand tiles and add them into Tiles
 * @param {type}
 * @return {type}
 */
function recycleHand() {
    return document.querySelectorAll(".tileRack>img").length;
}


/**
 * @description: game next
 * @param {type}
 * @return {type}
 */
function nextWord(isReset = false) {
    Board = ['', '', '', '', '', '', '']
    prevBoard = ['', '', '', '', '', '', '']
    if (!isReset) {
        $('.dragItem.ui-draggable.ui-draggable-handle').each(function() {
            let flag = 0
            $.each(this.attributes, function() {
                if (this.name == 'style' && this.value.indexOf('none') > -1) {
                    flag = 1
                }
            });
            if (flag == 0) {
                $.each(this.attributes, function() {
                    if (this.name === 'letter') {
                        Tiles[this.value].currCount++; //recycle tiles
                    }
                });
            }
        });
        // highestScore += score
        if (score > highestScore) {
            highestScore = score
        }
        $('#highest').html(`<span>${highestScore}</span>`)
    }
    $('.tileRack').empty()
    $('.dragItem').remove()
    $('#oneWordCheckIcon').addClass('instructionIcon')
    $('#minLengthIcon').addClass('instructionIcon')
    $('#dictionaryCheckIcon').addClass('instructionIcon')
    $("#nextWordButton").attr('disabled', true);
    $('#word').html(`<span></span>`)
    initTileBoard(isReset)
}

/**
 * @description: game reset
 * @param {type}
 * @return {type}
 */
function reset() {
    nextWord(true)
    score = 0
    $('#word').html(`<span></span>`)
    $('#score').html(`<span>0</span>`)
}

/**
 * @description: generate int number
 * @param {type}
 * @return {type}
 */
function Random(min, max) {
    return Math.round(Math.random() * (max - min)) + min;
}

function initTiles() {
    Tiles["A"] = {
        "value": 1,
        "totalCount": 9,
        "currCount": 9,
        "image": "public/images/Scrabble_Tile_A.jpg"
    };
    Tiles["B"] = {
        "value": 3,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_B.jpg"
    };
    Tiles["C"] = {
        "value": 3,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_C.jpg"
    };
    Tiles["D"] = {
        "value": 2,
        "totalCount": 4,
        "currCount": 4,
        "image": "public/images/Scrabble_Tile_D.jpg"
    };
    Tiles["E"] = {
        "value": 1,
        "totalCount": 12,
        "currCount": 12,
        "image": "public/images/Scrabble_Tile_E.jpg"
    };
    Tiles["F"] = {
        "value": 4,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_F.jpg"
    };
    Tiles["G"] = {
        "value": 2,
        "totalCount": 3,
        "currCount": 3,
        "image": "public/images/Scrabble_Tile_G.jpg"
    };
    Tiles["H"] = {
        "value": 4,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_H.jpg"
    };
    Tiles["I"] = {
        "value": 1,
        "totalCount": 9,
        "currCount": 9,
        "image": "public/images/Scrabble_Tile_I.jpg"
    };
    Tiles["J"] = {
        "value": 8,
        "totalCount": 1,
        "currCount": 1,
        "image": "public/images/Scrabble_Tile_J.jpg"
    };
    Tiles["K"] = {
        "value": 5,
        "totalCount": 1,
        "currCount": 1,
        "image": "public/images/Scrabble_Tile_K.jpg"
    };
    Tiles["L"] = {
        "value": 1,
        "totalCount": 4,
        "currCount": 4,
        "image": "public/images/Scrabble_Tile_L.jpg"
    };
    Tiles["M"] = {
        "value": 3,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_M.jpg"
    };
    Tiles["N"] = {
        "value": 1,
        "totalCount": 6,
        "currCount": 6,
        "image": "public/images/Scrabble_Tile_N.jpg"
    };
    Tiles["O"] = {
        "value": 1,
        "totalCount": 8,
        "currCount": 8,
        "image": "public/images/Scrabble_Tile_O.jpg"
    };
    Tiles["P"] = {
        "value": 3,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_P.jpg"
    };
    Tiles["Q"] = {
        "value": 10,
        "totalCount": 1,
        "currCount": 1,
        "image": "public/images/Scrabble_Tile_Q.jpg"
    };
    Tiles["R"] = {
        "value": 1,
        "totalCount": 6,
        "currCount": 6,
        "image": "public/images/Scrabble_Tile_R.jpg"
    };
    Tiles["S"] = {
        "value": 1,
        "totalCount": 4,
        "currCount": 4,
        "image": "public/images/Scrabble_Tile_S.jpg"
    };
    Tiles["T"] = {
        "value": 1,
        "totalCount": 6,
        "currCount": 6,
        "image": "public/images/Scrabble_Tile_T.jpg"
    };
    Tiles["U"] = {
        "value": 1,
        "totalCount": 4,
        "currCount": 4,
        "image": "public/images/Scrabble_Tile_U.jpg"
    };
    Tiles["V"] = {
        "value": 4,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_V.jpg"
    };
    Tiles["W"] = {
        "value": 4,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_W.jpg"
    };
    Tiles["X"] = {
        "value": 8,
        "totalCount": 1,
        "currCount": 1,
        "image": "public/images/Scrabble_Tile_X.jpg"
    };
    Tiles["Y"] = {
        "value": 4,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_Y.jpg"
    };
    Tiles["Z"] = {
        "value": 10,
        "totalCount": 1,
        "currCount": 1,
        "image": "public/images/Scrabble_Tile_Z.jpg"
    };
    Tiles["_"] = {
        "value": 0,
        "totalCount": 2,
        "currCount": 2,
        "image": "public/images/Scrabble_Tile_Blank.jpg"
    };
}

function initSpace() {
    $('#spaceReplace').removeClass('none')
    for (let i = 0; i < 26; i++) {
        let letter = tileNumList[i]
        if (Tiles[letter].currCount > 0) {
            $('#spaceReplace').append($(`<img src=${Tiles[letter]["image"]} onClick="onSpareClick(${"'"+letter+"'"})" class="dragItem" letter=${letter} />`))
        }
    }
}

function onSpareClick(e) {
    $('#spaceReplace').empty()
    $('#spaceReplace').addClass('none')
    spareReplaceTIle = e
    $('#spareBoard').attr("src", Tiles[e]["image"]);
    Board[replaceIndex] = e
    culculateScore(Board)
        // if (i == 1 || i == 5) {
        //     score += (Tiles[e].value) * 2
        // } else {
        //     score += Tiles[e].value
        // }
}
