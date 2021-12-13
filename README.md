# Pim4_trabalhoacademico
    val dateStr = "01092020"
    val dd = dateStr.substring(0..1)
    val mm = dateStr.substring(2..3)
    val yy = dateStr.substring(6 until dateStr.length)

    //val DDYY = "$dd/$yyyy"
    val mmYY = "$mm/$yy"
    println(mmYY)
