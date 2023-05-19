bool Request::is_subdirectory(std::string parent_path, std::string child_path)
{
    char full_parent_path[PATH_MAX];
    char full_child_path[PATH_MAX];

    if (realpath(parent_path.c_str(), full_parent_path) == NULL)
        return false;
    if (realpath(child_path.c_str(), full_child_path) == NULL)
        return false;
    parent_path = std::string(full_parent_path);
    child_path = std::string(full_child_path);
    if (child_path.find(parent_path) == 0)
        return true;
    return false;
}