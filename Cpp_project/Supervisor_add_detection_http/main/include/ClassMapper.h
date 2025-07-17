#ifndef CLASS_MAPPER_H
#define CLASS_MAPPER_H


struct ClassMapper {
    static const std::vector<std::string> classes;
    
    // 通过索引获取类别名称
    static std::string get_class(int index) {
        if (index < 0 || index >= classes.size()) {
            return "unknown";
        }
        return classes[index];
    }
};

#endif