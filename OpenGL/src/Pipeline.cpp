//unsigned int buffer;
//GLCALL(glGenBuffers(1, &buffer));
//GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
//GLCALL(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW));      //���㻺����
//
//unsigned int ibo;   
//GLCALL(glGenBuffers(1, &ibo));
//GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));    //����������
//
//unsigned int vao;
//GLCALL(glGenVertexArrays(1, &vao));
//GLCALL(glBindVertexArray(vao));          //��������
//
//GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0))     //��һ�������Ӷ��㻺�����Ͷ�������
//GLCALL(glEnableVertexAttribArray(0));         //���ö�������
//
//GLCALL(glUseProgram(shader));      //����shader
//
//GLCALL(glUseProgram(0));
//GLCALL(glBindVertexArray(0));
//GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));        //���
//
//while (!glfwWindowShouldClose(window))
//{
//    GLCALL(glUseProgram(shader));
//    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
//    GLCALL(glBindVertexArray(vao));    //��
//
//    
//
//    GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));   //draw call
//}
