#include "icon_renderer.hpp"
#include "canvas.hpp"
#include "icon_texture_map.hpp"
#include "gl_util.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace dune3d {
IconRenderer::IconRenderer(Canvas &c) : BaseRenderer(c, Canvas::VertexType::ICON)
{
}

GLuint IconRenderer::create_vao(GLuint program, GLuint &vbo_out)
{
    GLuint origin_index = glGetAttribLocation(program, "origin");
    GLuint shift_index = glGetAttribLocation(program, "shift");
    GLuint vec_index = glGetAttribLocation(program, "vec");
    GLuint icon_x_index = glGetAttribLocation(program, "icon_x");
    GLuint icon_y_index = glGetAttribLocation(program, "icon_y");
    GLuint flags_index = glGetAttribLocation(program, "flags");
    GLuint vao, buffer;

    /* we need to create a VAO to store the other buffers */
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* this is the VBO that holds the vertex data */
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    CanvasChunk::IconVertex vertices[] = {{0, 0, 0, 0, 0, 0, 1}};
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* enable and set the position attribute */
    glEnableVertexAttribArray(origin_index);
    glVertexAttribPointer(origin_index, 3, GL_FLOAT, GL_FALSE, sizeof(CanvasChunk::IconVertex), 0);
    GL_CHECK_ERROR
    glEnableVertexAttribArray(vec_index);
    glVertexAttribPointer(vec_index, 3, GL_FLOAT, GL_FALSE, sizeof(CanvasChunk::IconVertex),
                          (void *)offsetof(CanvasChunk::IconVertex, vx));
    GL_CHECK_ERROR
    glEnableVertexAttribArray(shift_index);
    glVertexAttribPointer(shift_index, 2, GL_FLOAT, GL_FALSE, sizeof(CanvasChunk::IconVertex),
                          (void *)offsetof(CanvasChunk::IconVertex, xs));
    GL_CHECK_ERROR
    glEnableVertexAttribArray(icon_x_index);
    glVertexAttribIPointer(icon_x_index, 1, GL_UNSIGNED_SHORT, sizeof(CanvasChunk::IconVertex),
                           (void *)offsetof(CanvasChunk::IconVertex, icon_x));
    GL_CHECK_ERROR
    glEnableVertexAttribArray(icon_y_index);
    glVertexAttribIPointer(icon_y_index, 1, GL_UNSIGNED_SHORT, sizeof(CanvasChunk::IconVertex),
                           (void *)offsetof(CanvasChunk::IconVertex, icon_y));
    GL_CHECK_ERROR

    glEnableVertexAttribArray(flags_index);
    glVertexAttribIPointer(flags_index, 1, GL_UNSIGNED_INT, sizeof(CanvasChunk::IconVertex),
                           (void *)offsetof(CanvasChunk::IconVertex, flags));
    GL_CHECK_ERROR

    /* enable and set the color attribute */
    /* reset the state; we will re-enable the VAO when needed */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // glDeleteBuffers (1, &buffer);
    vbo_out = buffer;

    return vao;
}

void IconRenderer::realize()
{
    glGenTextures(1, &m_texture_icon);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture_icon);
    {
        auto atlas_pixbuf = Gdk::Pixbuf::create_from_resource("/org/dune3d/dune3d/icon_texture_atlas.png");
        assert(atlas_pixbuf->get_width() == atlas_pixbuf->get_height());
        m_texture_size = atlas_pixbuf->get_width();
        assert(atlas_pixbuf->get_colorspace() == Gdk::Colorspace::RGB);
        assert(atlas_pixbuf->get_bits_per_sample() == 8);
        assert(atlas_pixbuf->get_has_alpha() == false);

        const auto n_channels = atlas_pixbuf->get_n_channels();
        assert(n_channels == 3);

        const auto rowstride = atlas_pixbuf->get_rowstride();


        std::vector<uint8_t> texture_buf;
        texture_buf.resize(atlas_pixbuf->get_height() * atlas_pixbuf->get_width());

        auto pixels = atlas_pixbuf->get_pixels();
        for (unsigned int x = 0; x < m_texture_size; x++) {
            for (unsigned int y = 0; y < m_texture_size; y++) {
                guchar *p = pixels + y * rowstride + x * n_channels;
                texture_buf.at(x + y * m_texture_size) = 0xff - std::clamp((p[0] + p[1] + p[2]) / 3, 0, 255);
            }
        }

        // for (auto &x : texture_buf)
        //     x = 0xff;
        //  atlas_pixbuf->get_pixels()

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_texture_size, m_texture_size, 0, GL_RED, GL_UNSIGNED_BYTE,
                     texture_buf.data());
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    m_program = gl_create_program_from_resource("/org/dune3d/dune3d/canvas/shaders/icon-vertex.glsl",
                                                "/org/dune3d/dune3d/canvas/shaders/icon-fragment.glsl",
                                                "/org/dune3d/dune3d/canvas/shaders/icon-geometry.glsl");
    m_vao = create_vao(m_program, m_vbo);
    m_ca.m_n_icons = 1;

    realize_base();

    GET_LOC(this, screen);
    GET_LOC(this, tex);
    GET_LOC(this, icon_size);
    GET_LOC(this, icon_border);
    GET_LOC(this, texture_size);
    GET_LOC(this, scale_factor);
}

void IconRenderer::push()
{
    m_ca.m_n_icons = 0;
    m_ca.m_n_icons_selection_invisible = 0;
    for (const auto &chunk : m_ca.m_chunks) {
        m_ca.m_n_icons += chunk.m_icons.size();
        m_ca.m_n_icons_selection_invisible += chunk.m_icons_selection_invisible.size();
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(CanvasChunk::IconVertex) * (m_ca.m_n_icons + m_ca.m_n_icons_selection_invisible), nullptr,
                 GL_STATIC_DRAW);

    // first buffer selection-visible vertices of all groups, then selection-invisble ones

    auto chunk_ids = m_ca.get_chunk_ids();
    size_t offset = 0;

    m_type_pick_base = m_ca.m_pick_base;
    for (const auto chunk_id : chunk_ids) {
        auto &chunk = m_ca.m_chunks.at(chunk_id);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(CanvasChunk::IconVertex) * offset,
                        sizeof(CanvasChunk::IconVertex) * chunk.m_icons.size(), chunk.m_icons.data());

        m_ca.m_vertex_type_picks[{m_vertex_type, chunk_id}] = {.offset = m_ca.m_pick_base,
                                                               .count = chunk.m_icons.size()};
        m_ca.m_pick_base += chunk.m_icons.size();
        offset += chunk.m_icons.size();
    }
    for (const auto chunk_id : chunk_ids) {
        auto &chunk = m_ca.m_chunks.at(chunk_id);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(CanvasChunk::IconVertex) * offset,
                        sizeof(CanvasChunk::IconVertex) * chunk.m_icons_selection_invisible.size(),
                        chunk.m_icons_selection_invisible.data());

        offset += chunk.m_icons_selection_invisible.size();
    }
}

void IconRenderer::render()
{
    if (!m_ca.m_n_icons && !m_ca.m_n_icons_selection_invisible)
        return;
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE1);
    glUniform1i(m_tex_loc, 1);
    glUniform1f(m_icon_size_loc, IconTexture::icon_size);
    glUniform1f(m_icon_border_loc, IconTexture::icon_border);
    glUniform1f(m_texture_size_loc, m_texture_size);
    glUniform1f(m_scale_factor_loc, m_ca.m_scale_factor);
    glBindTexture(GL_TEXTURE_2D, m_texture_icon);


    glUniformMatrix3fv(m_screen_loc, 1, GL_FALSE, glm::value_ptr(m_ca.m_screenmat));
    load_uniforms();

    glDrawArrays(GL_POINTS, 0, m_ca.m_n_icons);
    glColorMaski(1, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDrawArrays(GL_POINTS, m_ca.m_n_icons, m_ca.m_n_icons_selection_invisible);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

} // namespace dune3d
