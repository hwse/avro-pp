#include <avro/GenericDatum.hh>
#include <avro/Generic.hh>
#include <avro/DataFile.hh>
#include <cstdlib>
#include <fmt/format.h>

void pretty_print(const char *data_file_path)
{
    avro::DataFileReader<avro::GenericDatum> data_file(data_file_path);
    avro::GenericDatum message{};
    size_t i = 0;
    while (data_file.read(message))
    {
        ++i;
    }
    fmt::println("read {} messages!", i);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fmt::println("usage: avro-pp [path to avro data file]");
        return EXIT_FAILURE;
    }
    try
    {
        pretty_print(argv[1]);
    }
    catch (const std::exception &e)
    {
        fmt::println("error: {}", e.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        fmt::println("error: unknown exception");
        return EXIT_FAILURE;
    }
    return 0;
}